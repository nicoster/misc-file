//
//  CSIAnalytics.m


#import "CSIAnalytics.h"
//#import "CSILog.h"
//#import "CSINetworkReachability.h"
//#import "NSString+CSIExtensions.h"

#ifdef TARGET_OS_IPHONE
#import "UIDevice+CSIExtensions.h"
#endif

#include <stdlib.h>

//////////////////////////////////////
#pragma mark NSDictionary keys 
//////////////////////////////////////
static NSString *kCSIAnalyticsTrackingIDKey = @"CSIAnalyticsTrackingID";
static NSString *kCSIAnalyticsFirstVisitTimeKey = @"CSIAnalyticsFirstVisitTime";
static NSString *kCSIAnalyticsLastVisitTimeKey = @"CSIAnalyticsLastVisitTime";
static NSString *kCSIAnalyticsCurrentVisitTimeKey = @"CSIAnalyticsCurrentVisitTime";
static NSString *kCSIAnalyticsNumberOfVisitsKey = @"CSIAnalyticsNumberOfVisits";
static NSString *kCSIAnalyticsAdSenseHIDKey = @"CSIAnalyticsAdSenseHIDKey";
static NSString *kCSIAnalyticsCleanShutdownKey = @"kCSIAnalyticsCleanShutdownKey";
static NSString *kCSIAnalyticsTotalRuntimeOfLastVisitTimeKey = @"kCSIAnalyticsTotalRuntimeOfLastVisitTimeKey";
static NSString *kCSIAnalyticsNumberOfLowMemoryWarningsKey = @"kCSIAnalyticsNumberOfLowMemoryWarningsKey";

//////////////////////////////////////
#pragma mark Info.plist keys 
//////////////////////////////////////
static const CFStringRef kCSIAnalyticsAccountKey = CFSTR("CSIAnalyticsAccount");
static const CFStringRef kCSIAnalyticsTrackingModeKey = CFSTR("CSIAnalyticsTrackingMode");

//////////////////////////////////////
#pragma mark Constants
//////////////////////////////////////
static NSString* const baseURL = @"http://www.google-analytics.com/__utm.gif"; /* Base URL */
static NSString* const googleAnalyticsVersion = @"4.3";		 /*Tracking code version*/
static NSString* const screenColors = @"32-bit";	 //Screen color depth - FIXME: this should come from the system
static NSString* const language = @"en-us";	 //Application's language - FIXME: this needs to be obtained based on the localization we are using
static NSUInteger const domainHash = 1; //FIXME: This needs to be understood better.
static NSUInteger const numMinsUntilTimeout = 5; //Number of minutes after the system sleeps before a new session is started

//////////////////////////////////////
#pragma mark Private methods 
//////////////////////////////////////
@interface CSIAnalytics()
@property (nonatomic, readwrite, retain) NSString*	campaignContent;
@property (nonatomic, readwrite, retain) NSString*	campaignSource;
@property (nonatomic, readwrite, retain) NSString*	screenResolution;
@property (nonatomic, readwrite, assign) NSUInteger firstVisitInSeconds;
@property (nonatomic, readwrite, assign) NSUInteger lastVisitInSeconds;
@property (nonatomic, readwrite, assign) NSUInteger currentVisitInSeconds;
@property (nonatomic, readwrite, assign) NSUInteger numberOfVisits;
@property (nonatomic, readwrite, assign) NSUInteger adSenseHID;
@property (nonatomic, readwrite, assign) NSUInteger totalRuntimeOfLastVisitInSeconds;
@property (nonatomic, readwrite, assign) NSUInteger timeoutStartInSeconds;
@property (nonatomic, readwrite, assign) NSUInteger numberOfLowMemoryWarnings;
@property (nonatomic, readwrite, assign, getter=isStarted) BOOL started;
@property (nonatomic, readwrite, retain) NSString* productName;
@property (nonatomic, readwrite, retain) NSMutableSet *connections;

- (void)startNewSession;
- (void)resetCookie;
- (NSString*)_baseURLStringForPagePath:(NSString*)pagePath title:(NSString*)title;
- (NSString*)cookie;
- (void)sendRequest:(NSURL*)requestURL;
- (void)willResignActive:(NSNotification *)notif;
- (void)didBecomeActive:(NSNotification *)notif;

@end

@implementation CSIAnalytics
@synthesize trackingMode = myTrackingMode;
@synthesize analyticsAccount = myAnalyticsAccount;
@synthesize hostName = myHostName;
@synthesize referrer = myReferrer;
@synthesize campaign = myCampaign;
@synthesize campaignContent = myCampaignContent;
@synthesize campaignSource = myCampaignSource;
@synthesize previousPagePath = myPreviousPagePath;
@synthesize previousTitle = myPreviousTitle;
@synthesize timeoutStartInSeconds = myTimeoutStartInSeconds;
@synthesize screenResolution = myScreenResolution;
@synthesize screenColors = myScreenColors;
@synthesize started = myStarted;
@synthesize productName = myProductName;
@synthesize accountName = myAccountName;
@synthesize connections = myConnections;

static CSIAnalytics *theSharedAnalytics = nil;

+ (id)sharedAnalytics
{
	if (theSharedAnalytics == nil)
	{
		theSharedAnalytics = [[self alloc] init];
	}
	return theSharedAnalytics;
}

+ (void)setSharedAnalytics:(CSIAnalytics *)anAnalytics
{
	if (theSharedAnalytics != anAnalytics)
	{
		[anAnalytics retain];
		[theSharedAnalytics release];
		theSharedAnalytics = anAnalytics;
	}
}		

- (void)startAnalyticsWithAccountName:(NSString *)anAccountName
{
	if (self.isStarted)
	{
//		CSILogWarning(@"Restarting analytics. This will bump the session id.");
	}
	
	// Read the Google Analytics account number to be used for the project (from Info.plist)
	self.analyticsAccount = (NSString*)CFBundleGetValueForInfoDictionaryKey(CFBundleGetMainBundle(), kCSIAnalyticsAccountKey);
	if (self.analyticsAccount == nil)
	{
		self.analyticsAccount = @"undefined";		
	}
	
	// Reads in the project name from Info.plist
	self.productName = (NSString *)CFBundleGetValueForInfoDictionaryKey(CFBundleGetMainBundle(), kCFBundleNameKey);
	
	// Read the project settings to determine at what level Google Analytics should be enabled (from Info.plist)
	// But only allow tracking for release builds
	self.trackingMode = TrackingDetailed;

	// FIXME: Turning on analytics in DEBUG in order to trace down suspected crash in Analytics. rnapier 20110111.
//#ifndef CSI_DEBUG
	NSString *trackingModeValueInInfoDictionary = (NSString*)CFBundleGetValueForInfoDictionaryKey(CFBundleGetMainBundle(), kCSIAnalyticsTrackingModeKey);
	if (trackingModeValueInInfoDictionary != nil)
	{
		if ( [trackingModeValueInInfoDictionary isEqual:@"TrackingEnabled"] )
		{
			self.trackingMode = TrackingEnabled;
		}
		else if ( [trackingModeValueInInfoDictionary isEqual:@"TrackingDetailed"] )
		{
			self.trackingMode = TrackingDetailed;
		}
	}
//#endif
	
	// Announce CUET status in the log
//	switch (self.trackingMode)
//	{
//		case TrackingDisabled:
//		{
//			CSILogInfo(@"CUET Disabled");
//			break;
//		}
//		case TrackingEnabled:
//		{
//			CSILogInfo(@"CUET Disabled");
//			break;
//		}
//		case TrackingDetailed:
//		{
//			CSILogInfo(@"CUET Detailed (%@)", anAccountName);
//			break;
//		}
//		default:
//		{
//			CSILogError(@"CUET Unknown");
//			break;
//		}
//	}
			
	// Assign the native OS version to the campaign content
	self.campaignContent = [[NSProcessInfo processInfo] operatingSystemVersionString];
	
#ifdef TARGET_OS_IPHONE
	// Assign the device model being used
	self.campaignSource = [[UIDevice currentDevice] modelDetailed];
	
	// Assign the screen resolution
	CGRect screenBounds = [[UIScreen mainScreen] bounds];
	self.screenResolution = [NSString stringWithFormat:@"%.0fx%.0f", screenBounds.size.height, screenBounds.size.width];
	
	// Register for notifications.  These are used to reset the total runtime sent to Google if inactive for long periods
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willResignActive:) name:UIApplicationWillResignActiveNotification object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
#endif
	
	self.accountName = anAccountName; 
	self.started = YES;
	[self startNewSession];
}

- (void)sendStartupMessage
{
	if (self.trackingMode > TrackingDisabled)
	{
		// Check if the last run crashed.  If so, send a message.  (the next line checks to see if the program has ever been run before, if not, don't send the message)
		if ([self firstVisitInSeconds] != [self currentVisitInSeconds])
		{
			//self.hostName is not yet defined
			self.previousTitle = @"Launch";
			self.previousPagePath = @"/Launch";
			
			if ([[NSUserDefaults standardUserDefaults] boolForKey:kCSIAnalyticsCleanShutdownKey] == NO)
			{
				// there was an improper shutdown.  send a GA request.  report the number of low memory warnings recorded before crash
				NSString *numberOfLowMemoryWarningsString = [NSString stringWithFormat:@"%u", self.numberOfLowMemoryWarnings];
				[self trackEventForCategory:@"Shutdown" action:@"Improper" label:nil value:numberOfLowMemoryWarningsString];
			}
			else
			{
				// sanity check, we were getting extremely large numbers.  most likely due to the user defaults not being saved properly?
				// or self.currentVisitInSeconds being somehow set to zero on save? for now, arbitrarily chosing 1 year (3,1556,926 seconds)
				// as the cutoff time.  if a user runs the program for longer than that, we'll lost that data.
				// TODO: save last start time in seconds, and final time.  calculate as needed.  that will allow the numbers to be inspected for 0
				if (self.totalRuntimeOfLastVisitInSeconds > 31556926)
				{
					self.totalRuntimeOfLastVisitInSeconds = 0;
//					CSILogWarning(@"[CSIAnalytics sendStartupMessage] self.totalRuntimeOfLastVisitInSeconds > one year");
				}
				
				NSString *totalTimeRunningString = [NSString stringWithFormat:@"%u", self.totalRuntimeOfLastVisitInSeconds];
				[self trackEventForCategory:@"Shutdown" action:@"Proper" label:nil value:totalTimeRunningString];
			}
		}
		else
		{
			[self trackEventForCategory:@"Shutdown" action:@"Initial Launch" label:nil value:nil];
		}		
	}
	
	// Reset the number of memory warnings to zero
	self.numberOfLowMemoryWarnings = 0;
	
	// Set clean shutdown flag as false
	[[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithBool:NO] forKey:kCSIAnalyticsCleanShutdownKey];
		
	// Save defaults to disk
	[[NSUserDefaults standardUserDefaults] synchronize];
	
}

- (void)saveShutdownMessageInfo
{
	if (self.trackingMode > TrackingDisabled)
	{
		self.totalRuntimeOfLastVisitInSeconds = (NSUInteger)floor([[NSDate date] timeIntervalSince1970]) - self.currentVisitInSeconds;
	}
	else
	{
		self.totalRuntimeOfLastVisitInSeconds = 0;
	}
	
	[[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithBool:YES] forKey:kCSIAnalyticsCleanShutdownKey];
}

- (void)trackMemoryWarning
{
	int numMemoryWarnings = 0;
	
	if (self.trackingMode > TrackingDisabled)
	{
		// post an event reporting the low memory warning
		[self trackEventForCategory:@"Error" action:@"Warning" label:@"applicationDidReceiveMemoryWarning" value:nil];
		
		// read the last number of memory warnings, increment, and save it again.  to be reported if there is an improper shutdown
		numMemoryWarnings = self.numberOfLowMemoryWarnings;
		numMemoryWarnings++;
	}
	
	self.numberOfLowMemoryWarnings = numMemoryWarnings;
	
	// Save defaults to disk
	[[NSUserDefaults standardUserDefaults] synchronize];
}

- (id)init
{
	[super init];
		
	self.trackingMode = TrackingDisabled;
	self.connections = [NSMutableSet set];
	
	return self;
}

- (void)dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	
	[myPreviousPagePath release];
	myPreviousPagePath = nil;
	
	[myPreviousTitle release];
	myPreviousTitle = nil;
	
	[myAccountName release];
	myAccountName = nil;
	
	[myCampaignContent release];
	myCampaignContent = nil;
	
	[myCampaignSource release];
	myCampaignSource = nil;
	
	[myHostName release];
	myHostName = nil;
	
	[myReferrer release];
	myReferrer = nil;
	
	[myCampaign release];
	myCampaign = nil;
	
	[myAnalyticsAccount release];
	myAnalyticsAccount = nil;
	
	[myScreenResolution release];
	myScreenResolution = nil;
	
	[myScreenColors release];
	myScreenColors = nil;
	
	[myProductName release];
	myProductName = nil;
	
	[myConnections makeObjectsPerformSelector:@selector(cancel)];
	[myConnections release];
	myConnections = nil;
	
	[super dealloc];	
}

- (void)clearCookie
{
	// clear the random trackingID (unique number for each client)
	self.trackingID = 0;
	
	// clear the random AdSense ID
	self.adSenseHID = 0;
	
	// clear the first, last, and current visits		
	self.firstVisitInSeconds = 0;
	self.lastVisitInSeconds = 0;
	self.currentVisitInSeconds = 0;
	
	// clear the session numbers
	self.numberOfVisits = 0;
}	

- (void)resetCookie
{
	NSUInteger currentDateInSeconds = (NSUInteger)floor([[NSDate date] timeIntervalSince1970]);
	
	// pick non-personally identifiable phone id.  Could this be [UIDevice currentDevice].uniqueidentifier ?
	self.trackingID = random();
	
	// pick a random AdSense identification number
	self.adSenseHID = random();
	
	// set the first, last, and current visit to now		
	self.firstVisitInSeconds = currentDateInSeconds;
	self.lastVisitInSeconds = currentDateInSeconds;
	self.currentVisitInSeconds = currentDateInSeconds;
	
	// set this as the first session number
	self.numberOfVisits = 1;
}	

- (void)startNewSession
{
//	CSILogDebugTrace();
	NSUInteger currentDateInSeconds = (NSUInteger)floor([[NSDate date] timeIntervalSince1970]);
	
	// update last and current visits
	self.lastVisitInSeconds = self.currentVisitInSeconds;
	self.currentVisitInSeconds = currentDateInSeconds;
	
	// update session count
	self.numberOfVisits = self.numberOfVisits+1;	
}

- (void)trackError:(NSError*)error
{
	NSString *aLabel = [NSString stringWithFormat:@"%@ [%@:%d]", [error localizedDescription], [error domain], [error code]];
	[self trackEventForCategory:@"Error" action:@"Error" label:aLabel value:nil];
}


- (void)trackError:(NSError*)error level:(NSString *)errorLevel
{
	NSString *aLabel = [NSString stringWithFormat:@"%@ [%@:%d]", [error localizedDescription], [error domain], [error code]];
	[self trackEventForCategory:@"Error" action:errorLevel label:aLabel value:nil];
}

#ifdef TARGET_OS_IPHONE
- (void)trackPageviewForViewController:(UIViewController*)topViewController
{
	if (self.trackingMode > TrackingDisabled) {
		NSString *title = nil;
		NSString *path = @"/";
		NSArray *viewControllers = nil;
		
		if (topViewController.navigationController == nil)
		{
			viewControllers = [NSArray arrayWithObject:topViewController];
		}
		else
		{
			viewControllers = topViewController.navigationController.viewControllers;
		}
		
		for(UIViewController* viewController in viewControllers)
		{
			if([viewController respondsToSelector:@selector(analyticsTitle)])
			{
				title = [viewController analyticsTitle];
			}
			else
			{
				if([[viewController title] length] > 0) 
				{
					title = [viewController title];
				}
				else if ( [[viewController navigationItem].title length] > 0)
				{
					title = [viewController navigationItem].title;
				}
				else
				{
					title = @"Not Assigned";
				}
			}
			
			path = [path stringByAppendingPathComponent:title];
		}
		
//		path = [path stringByRemovingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
		
		[self trackPageviewForPath:path title:title];
	}
}
#endif

- (void)trackPageviewForPath:(NSString*)pagePath title:(NSString*)title
{	
	if (self.trackingMode > TrackingDisabled) {
		self.previousPagePath = pagePath;
		self.previousTitle = title;
		
		NSString *utmcc = [(NSString*)CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, 
																			(CFStringRef)[self cookie], 
																			NULL, 
																			(CFStringRef)@"/=;+", 
																			kCFStringEncodingUTF8) autorelease];
		
		NSString *requestString = [NSString stringWithFormat:@"%@&utmcc=%@", [self _baseURLStringForPagePath:pagePath title:title], utmcc];
		NSURL* requestURL = [NSURL URLWithString:requestString];
		[self sendRequest:requestURL];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//  IMPORTANT: Do not call methods or macros defined in CSILog from this method. E.g. CSILogError
//  CSILogWarning, CSILogBug, CSIAssert etc, unless you want to create infinite recursive calls!
/////////////////////////////////////////////////////////////////////////////////////////////////
- (void)trackEventForCategory:(NSString*)category action:(NSString*)action label:(NSString*)label value:(NSString*)value
{
	// THIS MAY BE ON A BACKGROUND THREAD
	if (self.trackingMode > TrackingDisabled) {
		
		category = [category stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
		action = [action stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
		label = [label stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
		
		//Assemble the event parameters
		NSString *utme;
		
		if (value != nil)
		{
			//Turn nil label into an empty string.  otherwise (null) appears in the output
			if (label == nil) label = @"";
			
			//Events are passed with the following fields: Category, Action, Label, and Value
			utme = [NSString stringWithFormat:@"5(%@*%@*%@)(%@)", category, action, label, value];
		} 
		else if (label != nil)
		{
			utme = [NSString stringWithFormat:@"5(%@*%@*%@)", category, action, label];
		}
		else
		{
			utme = [NSString stringWithFormat:@"5(%@*%@)", category, action];
		}
		
		NSString *utmcc = [(NSString*)CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, 
																			  (CFStringRef)[self cookie], 
																			  NULL, 
																			  (CFStringRef)@"/=;+", 
																			  kCFStringEncodingUTF8) autorelease];	
		
		//Finish creating the URL, and send the request to Google Analytics
		NSString *requestString = [NSString stringWithFormat:@"%@&utmt=event&utme=%@&utmcc=%@", [self _baseURLStringForPagePath:self.previousPagePath title:self.previousTitle], utme, utmcc];
		NSURL* requestURL = [NSURL URLWithString:requestString];
		[self performSelectorOnMainThread:@selector(sendRequest:) withObject:requestURL waitUntilDone:NO];
	}
}

- (void)setHostName:(NSString*)aHostName
{
	[aHostName retain];
	[myHostName release];
	myHostName = aHostName;
}

- (NSString*)hostName
{
	if(myHostName == nil)
	{
		return @"Not assigned";
	}
	
	return myHostName;
}

- (NSString*)referrer
{
	if(myReferrer == nil)
	{
		return @"0";
	}
	return myReferrer;
}

// The campaign (aka utmccn) is a user-defined value.  In Snowbird, it's being used for the server version
- (NSString *)campaign
{
	if (myCampaign == nil)
	{
		return @"Not Assigned";
	}

	return myCampaign;
}

// The campaign content (aka utmcct) is a user-defined value.  In Snowbird, it's being used for the iPhone OS version
- (NSString *)campaignContent
{
	if (myCampaignContent == nil)
	{
		return @"Not Assigned";
	}
	
	return myCampaignContent;
}

// The campaign source (aka utmcsr) is a user-defined value.  In Snowbird, it's being used for the device model
- (NSString *)campaignSource
{
	if (myCampaignSource == nil)
	{
		return @"Not Assigned";
	}
	
	return myCampaignSource;
}

- (NSString *)screenResolution
{
	if (myScreenResolution == nil)
	{
		return @"Unknown";
	}
	
	return myScreenResolution;
}

- (NSString *)screenColors
{
	if([myScreenColors length] == 0)
	{
		return @"Not Assigned";
	}
	
	return myScreenColors;
}

- (void)setScreenColors:(NSString *)theScreenColors
{
	[theScreenColors retain];
	[myScreenColors release];
	myScreenColors = theScreenColors;
}

- (NSString*)previousTitle
{
	if(myPreviousTitle == nil)
	{
		return @"Not Assigned";
	}
	return myPreviousTitle;
}

- (NSString*)previousPagePath
{
	if(myPreviousPagePath == nil)
	{
		return @"/PathNotAssigned";
	}
	return myPreviousPagePath;
}

- (NSString*)_baseURLStringForPagePath:(NSString*)pagePath title:(NSString *)title
{
	NSString *utmn = [NSString stringWithFormat:@"%d", random()]; //Random 32 bit number, to prevent browsers from caching identical requests
	NSString *utmdt = [title stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]; 
	NSString *utmp = [pagePath stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString *utmhn = [self.hostName stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString *utmwv = [googleAnalyticsVersion stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString *utmsr = [self.screenResolution stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString *utmsc = [self.screenColors stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString *utmul = [language stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString *utmr = [self.referrer stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString *utmac = [self.analyticsAccount stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString* utmfl = (NSString *)CFBundleGetValueForInfoDictionaryKey(CFBundleGetMainBundle(), kCFBundleVersionKey);
	utmfl = utmfl == nil ? @"Not assigned" : [utmfl stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]; 
	
	return [NSString stringWithFormat:@"%@?utmwv=%@&utmn=%@&utmhn=%@&utmsr=%@&utmsc=%@&utmul=%@&utmfl=%@&utmdt=%@&utmhid=%u&utmr=%@&utmp=%@&utmac=%@", baseURL, utmwv, utmn, utmhn, utmsr, utmsc, utmul, utmfl, utmdt, self.adSenseHID, utmr, utmp, utmac];
}

- (NSString*)cookie
{	
	/*Cookie values: __utma is for identifying unique visitors; 
	 __utmz is for tracking trafiic sources and navigation;
	 __utmv is for custom tracking */

	//TODO: some of the data here like domainHash, utmz, need to be understood more 
	//so that we know how to report accurate data
	
	NSString *utma = [NSString stringWithFormat:@"%d.%u.%d.%d.%d.%u;+", domainHash, 
					  self.trackingID, self.firstVisitInSeconds, 
					  self.lastVisitInSeconds, self.currentVisitInSeconds, 
					  self.numberOfVisits];
	
	// report the current ability to connect to the host
	NSString *utmcmd = nil;//[[CSINetworkReachability sharedReachability] internetConnectionDescription];
	
	NSString *utmz = [NSString stringWithFormat:@"%d.%d.1.1.utmcsr=%@|utmccn=%@|utmcct=%@|utmcmd=%@;+", 
					  domainHash, self.firstVisitInSeconds, self.campaignSource, self.campaign, self.campaignContent, utmcmd];
	
	NSString *utmv = nil;
	if (self.trackingMode >= TrackingDetailed)
	{
		utmv = [NSString stringWithFormat:@"%d.%@", domainHash, self.accountName];
		utmv = [(NSString*)CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, 
																(CFStringRef)utmv, 
																NULL, 
																(CFStringRef)@"%", 
																kCFStringEncodingUTF8) autorelease];
	}
	else
	{
		utmv = [NSString stringWithFormat:@"%d.", domainHash];
	}

	
	NSString *utmcc = [NSString stringWithFormat:@"__utma=%@__utmz=%@__utmv=%@;", utma, utmz, utmv];
	return utmcc;
}

- (void)sendRequest:(NSURL*)requestURL
{
	//Intentionally using NSAssert here because a call to CSIAssert would create a loop.
	//CSIAssert will ultimately call sendRequest, etc.

	// sendRequest isn't thread safe. It modifies an array, and it creates NSURLConnections,
	// which if created on a background thread need to be careful to preserve their runloop. 
	// Easiest solution is to just always call this on the main thread.
	NSAssert([NSThread currentThread] == [NSThread mainThread], @"Only call sendRequest on the main thread.");
	NSAssert(self.analyticsAccount != nil, @"No Analytics account number specified");
	
	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:requestURL];
	
	// Disabling the line below in order to return GA timeout to 60 seconds.  5 seconds was too short; it seems that sometimes startup messages (including improper/proper shutdown messages) were being lost
	// [request setTimeoutInterval:5]; // set timeout to 5 seconds.  default is 60 seconds
	NSString *versionNumberString = (NSString *)CFBundleGetValueForInfoDictionaryKey(CFBundleGetMainBundle(), kCFBundleVersionKey);

	#ifdef TARGET_OS_IPHONE
		NSString *deviceName = @"iPhone";
	#else
		NSString *deviceName = @"Unknown";
	#endif
	
	NSString *userAgent = [NSString stringWithFormat:@"%@/%@ (%@; U; CPU iPhone OS 2_0_0 like Mac OS X; en-us)", self.productName, versionNumberString, deviceName];
	[request setValue:userAgent forHTTPHeaderField:@"User-Agent"];

	NSURLConnection *connection = [NSURLConnection connectionWithRequest:request delegate:self];	
	[[self connections] addObject:connection];
	
	//NOTE: In the future, we may want to queue requests when the connection fails
	if (connection != nil) 
	{
		// FIXME: change to DEBUG after NSURLConnection crashes have been resolved.
//		CSILogInfo(@"-NSURL- CSIAnalytics: sendRequest [NSURLConnection connectionWithRequest]: %@ (%@)", connection, requestURL);
	} 
	else 
	{
//		CSILogWarning(@"-NSURL- [CSIAnalytics sendRequest] : sending data FAILED for %@", requestURL);
	}	
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection;
{
	// FIXME: change to DEBUG after NSURLConnection crashes have been resolved.
//	CSILogInfo(@"-NSURL- CSIAnalytics: connectionDidFinishLoading: %@", connection);
	[[self connections] removeObject:connection];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
#if defined(TARGET_OS_IPHONE) || (defined(MAC_OS_X_VERSION_10_6) && MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6)

	// FIXME: change to DEBUG after NSURLConnection crashes have been resolved.
//	CSILogInfo(@"-NSURL- CSIAnalytics: connection:didFailWithError: %@ (%@ - %@)",
//				connection,
//				[error localizedDescription],
//				[[error userInfo] objectForKey:NSURLErrorFailingURLStringErrorKey]);	
#else
	
	CSILogInfo(@"-NSURL- CSIAnalytics: connection:didFailWithError: %@ (%@ - %@)",
			   connection,
			   [error localizedDescription],
			   [[error userInfo] objectForKey:NSErrorFailingURLStringKey]); //this key is deprecated in MAC 10.6
#endif
	
	[[self connections] removeObject:connection];
}

- (NSUInteger)firstVisitInSeconds
{
	return [[NSUserDefaults standardUserDefaults] integerForKey:kCSIAnalyticsFirstVisitTimeKey];
}

- (void)setFirstVisitInSeconds:(NSUInteger)timeInSeconds
{
	[[NSUserDefaults standardUserDefaults] setInteger:timeInSeconds 
											   forKey:kCSIAnalyticsFirstVisitTimeKey];
}

- (NSUInteger)lastVisitInSeconds
{
	return [[NSUserDefaults standardUserDefaults] integerForKey:kCSIAnalyticsLastVisitTimeKey];
}

- (void)setLastVisitInSeconds:(NSUInteger)timeInSeconds 
{
	[[NSUserDefaults standardUserDefaults] setInteger:timeInSeconds 
											   forKey:kCSIAnalyticsLastVisitTimeKey];
}

- (NSUInteger)currentVisitInSeconds
{
	return [[NSUserDefaults standardUserDefaults] integerForKey:kCSIAnalyticsCurrentVisitTimeKey];
}

- (void)setCurrentVisitInSeconds:(NSUInteger)timeInSeconds
{
	[[NSUserDefaults standardUserDefaults] setInteger:timeInSeconds 
											   forKey:kCSIAnalyticsCurrentVisitTimeKey];
}

- (NSUInteger)numberOfVisits
{
	return [[NSUserDefaults standardUserDefaults] integerForKey:kCSIAnalyticsNumberOfVisitsKey];
}

- (void)setNumberOfVisits:(NSUInteger)numberOfVisits
{
	[[NSUserDefaults standardUserDefaults] setInteger:numberOfVisits 
											   forKey:kCSIAnalyticsNumberOfVisitsKey];
}

- (NSUInteger)trackingID
{
	return [[NSUserDefaults standardUserDefaults] integerForKey:kCSIAnalyticsTrackingIDKey];
}

- (void)setTrackingID:(NSUInteger)trackingID
{
	[[NSUserDefaults standardUserDefaults] setInteger:trackingID 
											   forKey:kCSIAnalyticsTrackingIDKey];
}

- (NSUInteger)adSenseHID
{
	return [[NSUserDefaults standardUserDefaults] integerForKey:kCSIAnalyticsAdSenseHIDKey];
}

- (void)setAdSenseHID:(NSUInteger)adSenseHID
{
	[[NSUserDefaults standardUserDefaults] setInteger:adSenseHID 
											   forKey:kCSIAnalyticsAdSenseHIDKey];
}

- (NSUInteger)totalRuntimeOfLastVisitInSeconds
{
	return [[NSUserDefaults standardUserDefaults] integerForKey:kCSIAnalyticsTotalRuntimeOfLastVisitTimeKey];
}

- (void)setTotalRuntimeOfLastVisitInSeconds:(NSUInteger)timeInSeconds
{
	[[NSUserDefaults standardUserDefaults] setInteger:timeInSeconds 
											   forKey:kCSIAnalyticsTotalRuntimeOfLastVisitTimeKey];
}

- (NSUInteger)numberOfLowMemoryWarnings
{
	return [[NSUserDefaults standardUserDefaults] integerForKey:kCSIAnalyticsNumberOfLowMemoryWarningsKey];
}

- (void)setNumberOfLowMemoryWarnings:(NSUInteger)numberOfLowMemoryWarnings
{
	[[NSUserDefaults standardUserDefaults] setInteger:numberOfLowMemoryWarnings 
											   forKey:kCSIAnalyticsNumberOfLowMemoryWarningsKey];
}

-(void)setTrackingMode:(CSIAnalyticsTrackingMode)trackingMode
{
	CSIAnalyticsTrackingMode lastTrackingMode = myTrackingMode;
	myTrackingMode = trackingMode;
	
	// Only resets the cookie if CUET (aka, GA) was previously disabled.  There's no need to reset it if tracking is already enabled
	if (self.trackingMode > TrackingDisabled && lastTrackingMode == TrackingDisabled) { 
		
		//Seed to guarantee a unique tracking ID
		srandom(time(NULL));
		
		//If cookie (app data residing on client) has never been set, then set it now
		if ([self firstVisitInSeconds] == 0)
		{
			[self resetCookie];
		} 
				
		//Save defaults to disk
		[[NSUserDefaults standardUserDefaults] synchronize];
	}
}

#pragma mark Notifications

- (void)willResignActive:(NSNotification *)notif
{
	self.timeoutStartInSeconds = (NSUInteger)floor([[NSDate date] timeIntervalSince1970]);
	
	// save the runtime up until the sleep state
	[self saveShutdownMessageInfo];
}

- (void)didBecomeActive:(NSNotification *)notif
{
	// if this is not the first run && the timeout time has elapsed, then start a new session
	// note: this methodology depends on when the system goes to sleep.  an alternate method would be to use
	// the last analytics event as the last active time and then to determine if a new session should be started
	// by looking at the time elapsed.  this was not used because there may be continuous error/warning messages
	// being sent in the background
	if ( self.timeoutStartInSeconds != 0 &&
		 (NSUInteger)floor([[NSDate date] timeIntervalSince1970]) > (self.timeoutStartInSeconds + numMinsUntilTimeout * 60) )
	{
		
		// if a timeout occurs, send a google analytics event with the runtime
		NSString *totalTimeRunningString = [NSString stringWithFormat:@"%u", self.totalRuntimeOfLastVisitInSeconds];
		
		// start a new session now, which will ensure that the total run time from before the timeout isn't double-counted
		[self startNewSession];

		// send the event with the proper session count (after the new session is started)
		[self trackEventForCategory:@"Shutdown" action:@"Timeout" label:nil value:totalTimeRunningString];
		
		
		//Save defaults to disk
		[[NSUserDefaults standardUserDefaults] synchronize];
	}
}

@end
