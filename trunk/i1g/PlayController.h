//
//  PlayControlBar.h
//
//  Created by Nick Xiao on 2/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@class PlaylistViewController;

@interface PlayController : UIViewController {
	PlaylistViewController* playlistView;
}

@property (nonatomic, retain) IBOutlet UIActivityIndicatorView* loadingIndicator; 
@property (nonatomic, retain) PlaylistViewController* playlistView;
- (IBAction) play: (id)sender;
- (IBAction) next: (id)sender;
- (id) initWithPlaylistView: (id) playlistView;

@end
