//
//  PlayControlBar.m
//
//  Created by Nick Xiao on 2/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlayController.h"
#import "AudioStreamer.h"
#import "i1GAppDelegate.h"
#import "NX1GClient.h"
#import "PlaylistViewController.h"


@implementation PlayController


@synthesize loadingIndicator, playlistView;


- (id) initWithPlaylistView: (id) aPlaylistView
{
	self = [super init];
	if (self == nil) return nil;
	
	self.playlistView = aPlaylistView;
	
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerStateDidChange:) name:@"ASStatusChangedNotification" object:nil];

	return self;
}

- (void)playerStateDidChange:(NSNotification *)notification;
{
	NSLog(@"as, state:%d", self.playlistView.player.state);
	[self.playlistView.player isWaiting] ? [self.loadingIndicator startAnimating] : [self.loadingIndicator stopAnimating];

}


- (void) dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver: self];
	self.playlistView = nil;
	[super dealloc];
}

- (IBAction) play: (id)sender
{
	AudioStreamer* player = self.playlistView.player;
	if ([player isPaused] || [player isPlaying]) {
		[self.playlistView play:nil];
	}
	else {
		[self.playlistView.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:YES scrollPosition:UITableViewScrollPositionNone];

		NXSong *song = [[[NX1GClient shared1GClient] playList] objectAtIndex: 0];
		NSString *url = [[song.urls objectAtIndex:0] url];		
		[self.playlistView play:url];
	}

}

- (IBAction) next: (id)sender
{
	[self.playlistView playNext];
}


@end
