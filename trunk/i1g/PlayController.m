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


@synthesize loadingIndicator, playlistView, player;


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
	NSLog(@"as, state:%d", player.state);
	[player isWaiting] ? [self.loadingIndicator startAnimating] : [self.loadingIndicator stopAnimating];

}


- (void) dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver: self];
	self.playlistView = nil;
	self.player = nil;
	[super dealloc];
}

- (IBAction) playPressed: (id)sender
{
	if ([player isPaused] || [player isPlaying]) {
		[self play:nil];
	}
	else {
		[self.playlistView.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:YES scrollPosition:UITableViewScrollPositionNone];

		NXSong *song = [[[NX1GClient shared1GClient] playList] objectAtIndex: 0];
		NSString *url = [[song.urls objectAtIndex:0] url];		
		[self play:url];
	}

}

- (IBAction) nextPressed: (id)sender
{
	[self.playlistView playNext];
}


- (void) play: (NSString*) aUrl
{
	if ([aUrl length])
	{
		NSURL *url = [NSURL URLWithString:aUrl];
		
		[player stop];
		self.player = [[[AudioStreamer alloc] initWithURL:url] autorelease];
		[player start];
	}
	else 
	{
		[player pause];	// pause will handle play/pause
	}
	
}


@end
