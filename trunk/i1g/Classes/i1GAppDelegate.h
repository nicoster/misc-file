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
@class NavigationSubviewController;

@interface i1GAppDelegate : NSObject <UIApplicationDelegate, UITabBarControllerDelegate> {
    UIWindow *window;
    
//    UITabBarController *tabBarController;
//	UIImage *imgSearch, *imgSetting, *imgPlaylist;

	PlaylistViewController *playlistController;
	SearchResultViewController *searchController;
	
	UINavigationController *captionBar;
    
    NavigationSubviewController *playlistContainer, *preferenceContainer, *searchContainer;
    
}

+ (i1GAppDelegate*) sharedAppDelegate;
@property (nonatomic, retain) IBOutlet UIWindow *window;
//@property (nonatomic, retain) IBOutlet UITabBarController *tabBarController;
//@property (nonatomic, retain) UIImage *imgSearch, *imgSetting, *imgPlaylist;

@property (nonatomic, retain) UINavigationController *captionBar;
@property (nonatomic, retain) SearchResultViewController *searchController;
@property (nonatomic, retain) PlaylistViewController *playlistController;

@property (nonatomic, retain) NavigationSubviewController *playlistContainer, *preferenceContainer, *searchContainer;
@property (nonatomic, retain) IBOutlet UILabel *promptBar;
@property (nonatomic, retain) IBOutlet UIView* overlay;

- (void) forView: (UIView*) parent showPrompt: (NSString*) formatString, ...;

@end
