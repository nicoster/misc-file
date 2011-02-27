//
//  PlayControlBar.h
//
//  Created by Nick Xiao on 2/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@class PlaylistViewController;
@class AudioStreamer;

@interface PlayController : UIViewController {
	PlaylistViewController* playlistView;
	AudioStreamer *player;
	UIButton *btnPlay, *btnNext;
	UIImage *imgPlay, *imgPause;
	bool btnPlayState;
}

@property (nonatomic, retain, readwrite) AudioStreamer *player;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView* loadingIndicator; 
@property (nonatomic, retain) PlaylistViewController* playlistView;
@property (nonatomic, retain) IBOutlet UIButton* btnPlay, *btnNext;
@property (nonatomic, retain) UIImage *imgPlay, *imgPause;

- (IBAction) playPressed: (id)sender;
- (IBAction) nextPressed: (id)sender;
- (id) initWithPlaylistView: (id) playlistView;
- (void) play: (NSArray*) urls;

@end
