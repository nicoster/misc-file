//
//  PlaylistViewController.h
//  i1G
//
//  Created by Nick Xiao on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PlayController;

@interface PlaylistViewController : UITableViewController 
{
	PlayController* playCtrl;
}

- (void) playNext;

@end
