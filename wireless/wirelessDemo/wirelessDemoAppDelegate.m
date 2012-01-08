//
//  wirelessDemoAppDelegate.m
//  wirelessDemo
//
//  Created by Max Qian on 11/18/11.
//  Copyright 2011 Cisco-Webex. All rights reserved.
//


#import "wirelessDemoAppDelegate.h"
#import "LauncherViewController.h"
#import "MovieSummaryController.h"
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
    [map from:@"tt://obj/(initwithobj:)" toViewController:self];
    
//    // test
//    NSDate *now = [NSDate date];
//    NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init]autorelease]; 
//    
//    
//    [dateFormatter setDateFormat:@"MM月dd日"];
//    //[dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
//    
//    NSString *destDateString = [dateFormatter stringFromDate:now];
//    NSLog(@"date:%@",destDateString);
//    // end


    
	[navigator openURLAction:
		 [TTURLAction actionWithURLPath:@"tt://launcher"]];
}


- (UIViewController*)initwithobj:(NSString *)className query:(NSDictionary *)obj 
{

    MovieInfo *p = [obj objectForKey:@"movieinfo"];

    UIViewController* newController = (UIViewController *)[[NSClassFromString(className) alloc] initwithObj:className info:p];
    [newController autorelease];
    return newController;
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
