//
//  PlaylistCell.h
//
//  Created by Nick Xiao on 3/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface PlaylistCell : UITableViewCell {
    IBOutlet UIView *accessoryView;
    IBOutlet UIView *backgroundView;
    IBOutlet UIView *editingAccessoryView;
    IBOutlet UIView *selectedBackgroundView;
	IBOutlet UILabel *title, *subtitle, *time;
	NSTimer *secondsTimer;
	NSString *reuseIdentifier;
	IBOutlet UIButton *btnAdd, *btnPlay;
}

- (void) updatePlayProgress: (bool) update;
@property (nonatomic, retain) UILabel *title, *subtitle, *time;
@property (nonatomic, retain) NSTimer *secondsTimer;
@property (nonatomic, copy) NSString *reuseIdentifier;
@property (nonatomic, retain) UIButton *btnAdd;

- (void) buttonAddPressed: (id) sender;

@end
