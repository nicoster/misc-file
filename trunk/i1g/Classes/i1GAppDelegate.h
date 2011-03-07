//
//  i1GAppDelegate.h
//  i1G
//
//  Created by Nick Xiao on 2/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#define BARBUTTON(TITLE, SELECTOR) 	[[[UIBarButtonItem alloc] initWithTitle:TITLE style:UIBarButtonItemStylePlain target:self action:SELECTOR] autorelease]
#define SYSBARBUTTON(ITEM, SELECTOR) [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:ITEM target:self action:SELECTOR] autorelease]

@class PlaylistViewController;
@class SearchResultViewController;

@interface i1GAppDelegate : NSObject <UIApplicationDelegate, UITabBarControllerDelegate> {
    UIWindow *window;
//    UITabBarController *tabBarController;
//	UIImage *imgSearch, *imgSetting, *imgPlaylist;
	IBOutlet PlaylistViewController *playlistController;
	
	UINavigationController *captionBar;
	SearchResultViewController *searchController;
}

+ (i1GAppDelegate*) sharedAppDelegate;
@property (nonatomic, retain) IBOutlet UIWindow *window;
//@property (nonatomic, retain) IBOutlet UITabBarController *tabBarController;
//@property (nonatomic, retain) UIImage *imgSearch, *imgSetting, *imgPlaylist;
@property (nonatomic, retain) UINavigationController *captionBar;
@property (nonatomic, retain) IBOutlet SearchResultViewController *searchController;
@property (nonatomic, retain) IBOutlet PlaylistViewController *playlistController;
@property (nonatomic, retain) IBOutlet UIViewController *playlistViewContainer;
@property (nonatomic, retain) IBOutlet UIViewController *searchViewContainer;
@property (nonatomic, retain) IBOutlet UILabel *promptBar;

- (void) forView: (UIView*) parent showPrompt: (NSString*) formatString, ...;

@end
