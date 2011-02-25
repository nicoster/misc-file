//
//  PlaylistViewController.h
//  i1G
//
//  Created by Nick Xiao on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AudioStreamer;

@interface PlaylistViewController : UITableViewController {
	AudioStreamer *player;
}
@property (nonatomic, retain, readwrite) AudioStreamer *player;
- (void) play: (NSString*) url;
- (void) playNext;

@end
