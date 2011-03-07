//
//  SongDetailViewController.m
//
//  Created by Nick Xiao on 2/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "SongDetailViewController.h"
#import "NX1GClient.h"

@implementation SongDetailViewController

@synthesize name, album, performer, song, remark;

- (id)initWithIndexPath: (NSIndexPath*) indexPath
{
	self = [super init];
	self.song = [[NX1GClient shared1GClient].playList objectAtIndex: indexPath.row];
	return self;
}

- (void) dealloc
{
	self.song = nil;
	self.name = self.album = self.performer = self.remark = nil;
	[super dealloc];
}



- (void)viewDidLoad
{
	[super viewDidLoad];

	name.text = self.song.title;
	album.text = self.song.album;
	performer.text = self.song.singer;
	remark.text = self.song.remark;
}

@end
