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

@interface PlaylistViewController : UITableViewController 
{
	PlayController* playCtrl;
	HttpConnectionId hidListNext;
}

+ (PlaylistViewController*) sharedPlaylistViewCtrlr;
- (void) playNext;

@end
