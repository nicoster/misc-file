//
//  SongDetailViewController.h
//
//  Created by Nick Xiao on 2/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>


@class NXSong;

@interface SongDetailViewController : UIViewController {
	NXSong *song;
}

- (id)initWithIndexPath: (NSIndexPath*) indexPath;
@property (nonatomic, retain) IBOutlet UILabel *name, *album, *performer, *remark;
@property (nonatomic, retain) NXSong *song;
@end
