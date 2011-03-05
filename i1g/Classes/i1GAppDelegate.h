//
//  i1GAppDelegate.h
//  i1G
//
//  Created by Nick Xiao on 2/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PlaylistViewController;

@interface i1GAppDelegate : NSObject <UIApplicationDelegate, UITabBarControllerDelegate> {
    UIWindow *window;
    UITabBarController *tabBarController;
	UIImage *imgSearch, *imgSetting, *imgPlaylist;
	IBOutlet PlaylistViewController *playlistController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UITabBarController *tabBarController;
@property (nonatomic, retain) UIImage *imgSearch, *imgSetting, *imgPlaylist;



@end
