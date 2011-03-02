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

#define TABS [@"Playlist Search Settings" componentsSeparatedByString:@" "]
//#define MAINLABEL	((UILabel *)self.navigationItem.titleView)


@implementation i1GAppDelegate

@synthesize window;
@synthesize tabBarController, imgSearch, imgSetting, imgPlaylist;



#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
	self.imgSearch = [UIImage imageNamed:@"search.png"];
	self.imgSetting = [UIImage imageNamed:@"setting.png"];
	self.imgPlaylist = [UIImage imageNamed:@"playlist.png"];
	
    // Override point for customization after application launch.
	NSMutableArray *ctrls = [NSMutableArray array];
	
	
	for (int i = 0; i < [TABS count]; i ++) {
		UITableViewController *tableview = nil;
		UINavigationController *nav = nil;
		switch (i) {
			case 0:
				tableview = [[PlaylistViewController alloc] init/*WithStyle:UITableViewStyleGrouped*/];
				[tableview.tabBarItem initWithTitle:nil image:imgPlaylist tag:0];
				break;
			case 1:
				tableview = [[SearchResultViewController alloc] initWithStyle:UITableViewStyleGrouped];
				[tableview.tabBarItem initWithTitle:nil image:imgSearch tag:0];
				break;
			case 2:
				tableview = [[PreferenceViewController alloc] init/*WithStyle:UITableViewStyleGrouped*/];
				[tableview.tabBarItem initWithTitle:nil image:imgSetting tag:0];
				nav = [[UINavigationController alloc] initWithRootViewController:tableview];
				break;
			default:		
				NSAssert(NO, @"too many tabs");
				break;
		}
		
		tableview.title = [TABS objectAtIndex:i];
		nav = [[UINavigationController alloc] initWithRootViewController:tableview];		

		[ctrls addObject: nav];
		[tableview release];
		[nav release];
	}
	
	tabBarController.viewControllers = ctrls;
	tabBarController.delegate = self;
	
    // Add the tab bar controller's view to the window and display.
    [self.window addSubview:tabBarController.view];
    [self.window makeKeyAndVisible];

    return YES;
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
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
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


- (void)dealloc {
    [tabBarController release];
	imgSearch = imgSetting = imgPlaylist = nil;
    [window release];
    [super dealloc];
}

@end

