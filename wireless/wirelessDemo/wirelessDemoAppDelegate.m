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
//	[map from:@"*" toViewController:[TTWebController class]];
    
    [map from:@"tt://launcher/" 
		toViewController: [LauncherViewController class]];
    
    
    [map from:@"tt://nib/(loadFromNib:)" toSharedViewController:self];
    
	[navigator openURLAction:
		 [TTURLAction actionWithURLPath:@"tt://launcher"]];
}

- (UIViewController*)loadFromNib:(NSString *)nibName withClass:className {
    UIViewController* newController = [[NSClassFromString(className) alloc]
                                       initWithNibName:nibName bundle:nil];
    [newController autorelease];
    
    return newController;
}

- (UIViewController*)loadFromNib:(NSString*)className {
    return [self loadFromNib:className withClass:className];
}


///////////////////////////////////////////////////////////////////////////////////////////////////
- (BOOL)navigator:(TTNavigator*)navigator shouldOpenURL:(NSURL*)URL {
    return YES;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
- (BOOL)application:(UIApplication*)application handleOpenURL:(NSURL*)URL {
    [[TTNavigator navigator] openURLAction:[TTURLAction actionWithURLPath:URL.absoluteString]];
    return YES;
}

@end
