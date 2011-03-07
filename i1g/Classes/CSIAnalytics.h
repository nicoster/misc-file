//
//  CSIAnalytics.h
//
//  This class provides an Objective-C API for Google Analytics, a hosted Web analytics tools 
//  that gathers data from JavaScript “page tags” called UTM (Urchin Tracking Monitor) tags
//  inserted into Web pages that are to be tracked.  The methods in this API are the equivalent 
//  of these page tags that would be called from different view controllers. The API 
//  communicates with Google Analytics servers by loading a 1-pixel transparent GIF file (__utm.gif) 
//  and passing all of the data in the HTTP request parameters.
//
//  Also see:
//		Google Analytics:		http://www.google.com/analytics/
//		Documentation:			http://code.google.com/apis/analytics/docs/index.html
//		Functional overview:	http://code.google.com/apis/analytics/docs/gaConceptsOverview.html
//		JavaScript APIs:		http://code.google.com/apis/analytics/docs/gaJSApi.html
//		GIF Request Parameters:	http://code.google.com/apis/analytics/docs/gaTrackingTroubleshooting.html#gifParameters
//
//  For explanation of local and instance variable of this class that begin with 'utm', refer to the 
//  'GIF Request Parameters' documentation.

#import <Foundation/Foundation.h>

typedef enum
{
	TrackingDisabled = 0,
	TrackingEnabled,
	TrackingDetailed
} CSIAnalyticsTrackingMode;


@interface CSIAnalytics : NSObject 
{
	NSString*	myAnalyticsAccount;			//Account string (aka, Web Property ID)
	NSString*	myHostName;					//Host name
	NSString*	myReferrer;					//Referring website
	NSString*	myCampaign;					//User-defined.  Used for the server version in Snowbird
	NSString*	myCampaignContent;			//User-defined.  Used for the iPhone OS version in Snowbird
	NSString*	myCampaignSource;			//User-defined.  Used for the device model
	NSString*	myPreviousPagePath;			//Keeps track of the last page that was visited.  For event tracking
	NSString*	myPreviousTitle;			//Keeps track of the last page that was visited.  For event tracking
	NSString*	myAccountName;			// Stored in "var" (user defined value) in cookie.
	CSIAnalyticsTrackingMode myTrackingMode;//Keeps track of the current logging level, including if CUET (aka, GA) is disabled
	NSUInteger  myTimeoutStartInSeconds;	//Keeps track of when the timeout timer started, used internally
											//  to decide when to start a new session
	NSString*	myScreenResolution;			//The screen resolution of the device
	NSString*   myScreenColors;				//Unity version being reported in place of screen colors
	BOOL myStarted;						// Have we started analytics?
	NSString *myProductName;	// Name of the product
	NSMutableSet *myConnections;			// Open connections
}

/*!
 Shared instance
 */
+ (id)sharedAnalytics;

/*!
 Set the shared instance (for use if a subclass is needed)
 */
+ (void)setSharedAnalytics:(CSIAnalytics *)anAnalytics;

/* startAnalytics - call this to read setting from Info.plist (or to populate all
   necessary fields with dummy values). Setting the account name is important to start
   the session correctly. Generally you shouldn't start analytics until you know the account.
*/
- (void)startAnalyticsWithAccountName:(NSString *)anAccountName;

/* sendStartupMessage - call this to keep track of intentional shutdowns
 */
- (void)sendStartupMessage;

/* sendShutdownMessage - call this to keep track of intentional shutdowns
 */
- (void)saveShutdownMessageInfo;

/* trackMemoryWarning - sends a memory warning message and caches the number of memory warnings received.
   The total number of memory warnings will be reported in case of an improper shutdown when 
   sendStartupMessage is called
 */
- (void)trackMemoryWarning;

/* trackError - to be used in cases when you wish to pass an NSError to GA
   @param error - the NSerror object whose contents are to be sent.
 */
- (void)trackError:(NSError*)error;

/* trackError:level - same as trackError: but with ability to specify
   error levels that will go into the action field for the GA event 
 */
- (void)trackError:(NSError*)error level:(NSString *)errorLevel;

#ifdef TARGET_OS_IPHONE
/* trackPageviewForViewController - same as trackPageviewForPath:title: but this
   is for iPhone platform only. This methods just take the viewcontroller as the 
   argument and figures out for itself the path and title
   @param: topViewController - the viewContoller that is currently visible and 
           whose path and title has to be dertemined
 */
- (void)trackPageviewForViewController:(UIViewController*)topViewController;
#endif

/* trackPageviewForPath - Records a single page view event. 
   @param pagePath: This can be whatever we want and doesn’t have to correspond to a real Web page URL
					For iPhone applications this will correspond to the path of a view controller from
					the tabBarViewController, which is on top of the hierarchy. The first word is the 
					name of the application. For e.g. /Meetings/Settings means the Settings tab of
					'Meetings' application. /Meetings/Settings/About is URL for 'About' page from Settings
					page.
 */
- (void)trackPageviewForPath:(NSString*)pagePath title:(NSString*)title;

/* trackEvent - Records user events.  
	@param: Can be used to record events: for button clicks, error logging, dialog boxes, etc.  The user
					should provide a category of event, the action performed, an optional label, and an
					optional numeric value (as a NSString).  If the optional value is not needed, insert
					a nil.
 */
- (void)trackEventForCategory:(NSString*)category action:(NSString*)action label:(NSString*)label value:(NSString*)value;

/* 
 Account name for user. This is ignored if tracking is below Detailed.
 You must call -startNewSession for this to take effect. We don't call it automatically
 because other cookie-influencing things might change.
*/
@property (nonatomic, readwrite, copy) NSString *accountName;

/* clearCookie - Clears the cookie data, including the number of visits and the time of the first visit
*/
- (void)clearCookie;

/* startNewSession - Increments the cookie data, including the number of visits.  Used when important data, like the username
	is changed that we want to be there at the start of the session in GA.  Use sparingly.
 */
- (void)startNewSession;

/*!
 The current tracking level (disabled, enabled, detailed). In detailed mode, we also track the accountname.
 If you change the tracking mode, you must call -startNewSession to take effect.
 */
@property (nonatomic, readwrite, assign) CSIAnalyticsTrackingMode trackingMode;

@property (nonatomic, readwrite, retain) NSString* analyticsAccount;
@property (nonatomic, readwrite, retain) NSString* hostName;
@property (nonatomic, readwrite, assign) NSUInteger trackingID;
@property (nonatomic, readwrite, retain) NSString* referrer;
@property (nonatomic, readwrite, retain) NSString* campaign;
@property (nonatomic, readwrite, retain) NSString* previousPagePath;
@property (nonatomic, readwrite, retain) NSString* previousTitle;
@property (nonatomic, readwrite, retain) NSString* screenColors;
@property (nonatomic, readonly, assign, getter=isStarted) BOOL started;
 
@end


#ifdef TARGET_OS_IPHONE
@interface UIViewController (CSIAnalytics)
- (NSString*)analyticsTitle;
@end
#endif
