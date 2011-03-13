//
//  PlaylistCell.h
//
//  Created by Nick Xiao on 3/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@class PlaylistViewController;

@interface PlaylistCell : UITableViewCell {
    IBOutlet UIView *accessoryView;
    IBOutlet UIView *backgroundView;
    IBOutlet UIView *editingAccessoryView;
    IBOutlet UIView *selectedBackgroundView;
	IBOutlet UILabel *title, *subtitle, *time;
	NSTimer *secondsTimer;
	NSString *reuseIdentifier;
	IBOutlet UIButton *btnAdd, *btnPlay;
    
    PlaylistViewController *playlistController;
}

- (void) updatePlayProgress: (bool) update;
@property (nonatomic, retain) UILabel *title, *subtitle, *time;
@property (nonatomic, retain) NSTimer *secondsTimer;
@property (nonatomic, copy) NSString *reuseIdentifier;
@property (nonatomic, retain) UIButton *btnAdd;
@property (nonatomic, retain) PlaylistViewController *playlistController;
- (void) buttonAddPressed: (id) sender;

@end
