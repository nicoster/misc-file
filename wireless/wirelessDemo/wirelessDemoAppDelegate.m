//
//  wirelessDemoAppDelegate.m
//  wirelessDemo
//
//  Created by Max Qian on 11/18/11.
//  Copyright 2011 Cisco-Webex. All rights reserved.
//


#import "wirelessDemoAppDelegate.h"
#import "LauncherViewController.h"
@implementation wirelessDemoAppDelegate

//@synthesize window = _window;
- (void)applicationDidFinishLaunching:(UIApplication *)application {
    TTNavigator* navigator = [TTNavigator navigator];
    navigator.persistenceMode = TTNavigatorPersistenceModeAll;
    TTURLMap* map = navigator.URLMap;
    
    [map from:@"tt://launcher/" 
		toViewController: [LauncherViewController class]];
    
	[navigator openURLAction:
		 [TTURLAction actionWithURLPath:@"tt://launcher"]];
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//- (BOOL)navigator:(TTNavigator*)navigator shouldOpenURL:(NSURL*)URL {
//    return YES;
//}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//- (BOOL)application:(UIApplication*)application handleOpenURL:(NSURL*)URL {
//    [[TTNavigator navigator] openURLAction:[TTURLAction actionWithURLPath:URL.absoluteString]];
//    return YES;
//}

@end
