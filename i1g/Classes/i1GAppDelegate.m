//
//  i1GAppDelegate.m
//  i1G
//
//  Created by Nick Xiao on 2/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "i1GAppDelegate.h"
#import "NX1GClient.h"
#import "AudioStreamer.h"
#import "PlayController.h"
#import "PlaylistViewController.h"
#import "SearchResultViewController.h"
#import "PreferenceViewController.h"
#import "NavigationSubviewController.h"

#import "CSIAnalytics.h"

//#define TABS [@"Playlist Search Settings" componentsSeparatedByString:@" "]
//#define MAINLABEL	((UILabel *)self.navigationItem.titleView)

NSString * const TITLE_PREFERENCE = @"设置";
NSString * const TITLE_MAIN = @"亦歌";
NSString * const TITLE_SEARCH = @"搜索";


@implementation i1GAppDelegate

@synthesize window, captionBar, searchController, playlistController, playlistContainer, preferenceContainer, searchContainer, promptBar, overlay;
//@synthesize tabBarController, imgSearch, imgSetting, imgPlaylist;

- (void)dealloc {
//    [tabBarController release];
//	self.imgSearch = self.imgSetting = self.imgPlaylist = nil;
	self.window = nil;
	self.captionBar = nil;
	self.searchController = nil;
	self.playlistController = nil;
	self.playlistContainer = nil;
	self.searchContainer = nil;
    self.preferenceContainer = nil;
	self.promptBar = nil;
    [window release];
    [super dealloc];
}

static i1GAppDelegate* theAppDelegate = nil;

+ (i1GAppDelegate*) sharedAppDelegate
{
	return theAppDelegate;
}

- (void) showSearchView: (id) sender
{
    if (searchContainer == nil) {
        self.searchContainer = [[NavigationSubviewController alloc] init];
 		searchContainer.title = TITLE_SEARCH;
   }
	if (searchController == nil) {
		self.searchController = [[SearchResultViewController alloc] initWithContainer:searchContainer];
		searchController.view = searchController.view;
	}
	[captionBar pushViewController:searchContainer animated:YES];
}

- (void) showPlaylistView: (id) sender
{
    BOOL animate = playlistContainer ? YES : NO;
    if (playlistContainer == nil) {
        self.playlistContainer = [[NavigationSubviewController alloc] init];
		playlistContainer.title = TITLE_MAIN;
    }
    
    if (playlistController == nil) {
        self.playlistController = [[PlaylistViewController alloc] initWithContainer: playlistContainer];
        playlistController.view = playlistController.view;
    }
	[captionBar pushViewController:playlistContainer animated:animate];
}

- (void) hidePrompt: (NSTimer*) timer
{
	[timer invalidate];
	timer = nil;
		
	CGContextRef context = UIGraphicsGetCurrentContext();
	[UIView beginAnimations:nil context:context];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
	[UIView setAnimationDuration:0.8];
	
	self.promptBar.superview.center = CGPointMake(160, -12);
	
	[UIView commitAnimations];
}

- (void) forView: (UIView*) parent showPrompt: (NSString*) formatString, ...
{
    va_list args;
    va_start(args, formatString);
    NSString *prompt = [[NSString alloc] initWithFormat:formatString arguments:args];
    va_end(args);
	
	[self.promptBar.superview removeFromSuperview];
	
	if (parent == nil) {
		parent = captionBar.visibleViewController.view;
	}
	self.promptBar.text = prompt;
	[parent addSubview: self.promptBar.superview];	
	self.promptBar.superview.center = CGPointMake(160, -12);
	
	CGContextRef context = UIGraphicsGetCurrentContext();
	[UIView beginAnimations:nil context:context];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
	[UIView setAnimationDuration:0.8];
	
	self.promptBar.superview.center = CGPointMake(160, 10);
	
//	[UIView setAnimationDidStopSelector:@selector(animationFinished:)];
	[UIView commitAnimations];
		
	[NSTimer scheduledTimerWithTimeInterval:1.2 target:self selector:@selector(hidePrompt:) userInfo:nil repeats:NO];
}

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
	
	NSLog(@"Start");
	NSString *user = [[NSUserDefaults standardUserDefaults] objectForKey:@"kPreferenceUser"];
	[[CSIAnalytics sharedAnalytics] startAnalyticsWithAccountName: [NSString stringWithFormat:@"%d", [user hash]]];
	[[CSIAnalytics sharedAnalytics] trackEventForCategory:@"launch" action:@"start" label:nil value:nil];
	
	theAppDelegate = self;
	application.applicationSupportsShakeToEdit = YES;
	
	{
        self.preferenceContainer = [[NavigationSubviewController alloc] init];
		PreferenceViewController *pref = [[PreferenceViewController alloc] initWithContainer: preferenceContainer];
        pref.view = pref.view;
		preferenceContainer.title = TITLE_PREFERENCE;
	
		captionBar = [[UINavigationController alloc] initWithRootViewController: preferenceContainer];
		preferenceContainer.navigationItem.rightBarButtonItem = BARBUTTON(TITLE_MAIN,@selector (showPlaylistView:));
		
        [self showPlaylistView:nil];
		playlistContainer.navigationItem.rightBarButtonItem = BARBUTTON(TITLE_SEARCH,@selector (showSearchView:));
		
		[self.window addSubview:captionBar.view];
		[self.window makeKeyAndVisible];
		
		return YES;
	}
	
//	self.imgSearch = [UIImage imageNamed:@"search.png"];
//	self.imgSetting = [UIImage imageNamed:@"setting.png"];
//	self.imgPlaylist = [UIImage imageNamed:@"playlist.png"];
//	
//    // Override point for customization after application launch.
//	NSMutableArray *ctrls = [NSMutableArray array];
//	
//	
//	for (int i = 0; i < [TABS count]; i ++) {
//		UIViewController *rootview = nil;
//		UINavigationController *nav = nil;
//		switch (i) {
//			case 0:
//			{
//				rootview = [[UIViewController alloc] init];
////				UITableViewController *tableview = [[[PlaylistViewController alloc] init/*WithStyle:UITableViewStyleGrouped*/] autorelease];
//				playlistController.view.frame = CGRectMake(0, 0, 320, 386);
//				
////				PlayController *play = [[PlayController alloc] initWithPlaylistView: playlistController];	
////				play.view.frame = CGRectMake(0, 292, 320, 75);
//				
//				UIToolbar *tb = [[UIToolbar alloc] initWithFrame:CGRectMake(0.0f, 292.0f, 320.0f, 75.0f)];
////				tb.center = CGPointMake(160.0f, 200.0f);
//				NSMutableArray *tbitems = [NSMutableArray array];
//				
//				UIBarButtonItem *bbi = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:nil] autorelease];
//				bbi.width = 20.0f;
//				[tbitems addObject:bbi];
//				[tbitems addObject:SYSBARBUTTON(UIBarButtonSystemItemPlay, @selector(action))];
//				bbi = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:nil] autorelease];
//				bbi.width = 20.0f;
//				[tbitems addObject:bbi];
//				[tbitems addObject:SYSBARBUTTON(UIBarButtonSystemItemFastForward, @selector(action))];
//				
//				tb.items = tbitems;
//				
//				[rootview.view addSubview: playlistController.view];
//				[rootview.view addSubview: tb];
//				[rootview.view addSubview: playlistController->overlay];
//				[rootview.tabBarItem initWithTitle:nil image:imgPlaylist tag:0];
//				break;
//			}
//			case 1:
//				rootview = [[SearchResultViewController alloc] initWithStyle:UITableViewStyleGrouped];
//				[rootview.tabBarItem initWithTitle:nil image:imgSearch tag:0];
//				break;
//			case 2:
//				rootview = [[PreferenceViewController alloc] init/*WithStyle:UITableViewStyleGrouped*/];
//				[rootview.tabBarItem initWithTitle:nil image:imgSetting tag:0];
//				break;
//			default:		
//				NSAssert(NO, @"too many tabs");
//				break;
//		}
//		
//		rootview.title = [TABS objectAtIndex:i];
//		nav = [[UINavigationController alloc] initWithRootViewController:rootview];	
//
//		
//		[ctrls addObject: nav];
//		[rootview release];
//		[nav release];
//	}
//	
//	tabBarController.viewControllers = ctrls;
//	tabBarController.delegate = self;
//	
//    // Add the tab bar controller's view to the window and display.
//    [self.window addSubview:tabBarController.view];
//    [self.window makeKeyAndVisible];
//	
//    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. 
	 This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or 
	 when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore 
	 your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, 
	 optionally refresh the user interface.
     */
}


- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark UITabBarControllerDelegate methods

/*
// Optional UITabBarControllerDelegate method.
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController {
}
*/

/*
// Optional UITabBarControllerDelegate method.
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray *)viewControllers changed:(BOOL)changed {
}
*/


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}



@end

