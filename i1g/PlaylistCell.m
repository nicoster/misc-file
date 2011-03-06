//
//  PlaylistCell.m
//
//  Created by Nick Xiao on 3/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlaylistCell.h"
#import "AudioStreamer.h"
#import "PlaylistViewController.h"
#import "NX1GClient.h"
#import "i1GAppDelegate.h"

@implementation PlaylistCell

@synthesize title, subtitle, time, secondsTimer, reuseIdentifier, btnAdd;

- (NX1GClient*) httpClient
{
	return [NX1GClient shared1GClient];
}

//- (id) init
- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)aReuseIdentifier {
	self = [super initWithStyle:style reuseIdentifier:aReuseIdentifier];
	secondsTimer = nil;
	return self;
}

- (void) buttonAddPressed: (id) sender
{
	NSIndexPath *indexPath = [(UITableView*)self.superview indexPathForCell:self];
	if ([self.reuseIdentifier isEqualToString:@"PlaylistCell"]) {
		NXSong *song = [[self.httpClient playList] objectAtIndex: indexPath.row];

		[self.httpClient addFavById:song.songId];
		
	}else {
		NSMutableArray *pl = [self.httpClient playList];
		NXSong *song = [[self.httpClient searchResults] objectAtIndex: indexPath.row];
		 		
		[pl insertObject: song atIndex: [pl count] ? 1 : 0];
		[[[[i1GAppDelegate sharedAppDelegate] playlistController] tableView] reloadData];
	}

}

- (void)handle1SecondTimer: (NSTimer*) theTimer
{	
	int progress = (int)[PlaylistViewController sharedPlaylistViewCtrlr].player.progress;
	int duration = (int)[PlaylistViewController sharedPlaylistViewCtrlr].player.duration;
	if (progress) {
		if (0) {
			self.time.text = [NSString stringWithFormat: @"%d:%02d/%d:%02d", progress / 60, progress % 60, duration / 60, duration % 60];
		}
		else {
			self.time.text = [NSString stringWithFormat: @"%d:%02d", progress / 60, progress % 60];
		}
	}
	else {
		self.time.text = @"";
	}

}

- (void) updatePlayProgress: (bool) update
{
	if (update) {
		self.secondsTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(handle1SecondTimer:) userInfo:nil repeats:YES];
	}
	else {
		self.time.text = @"";
		[self.secondsTimer invalidate];
		self.secondsTimer = nil;
	}

}

- (void) dealloc
{
	title = subtitle = time = nil;
	[secondsTimer invalidate];
	secondsTimer = nil;
	btnAdd = nil;
	reuseIdentifier = nil;
	
	[super dealloc];
}

@end
