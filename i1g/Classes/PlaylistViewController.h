//
//  PlaylistViewController.h
//  i1G
//
//  Created by Nick Xiao on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NXHttpClient.h"

@class PlayController;
@class AudioStreamer;

@interface PlaylistViewController : UITableViewController 
{
//	PlayController* playCtrl;
	AudioStreamer *player;

	HttpConnectionId hidListNext;
    
    UIViewController* container;
}

//@property (nonatomic, retain, readwrite) PlayController* playCtrl;
@property (nonatomic, retain) AudioStreamer *player;
@property (nonatomic, retain) UIViewController* container;
@end
