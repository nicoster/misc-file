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


@synthesize playlistView, player, btnPlay, btnNext, imgPlay, imgPause;


- (id) initWithPlaylistView: (id) aPlaylistView
{
	self = [super init];
	if (self == nil) return nil;
	
	self.playlistView = aPlaylistView;
	self.imgPlay = [UIImage imageNamed:@"play.png"];
	self.imgPause = [UIImage imageNamed:@"pause.png"];

//	btnPlayState = YES;
//	[btnPlay setBackgroundImage:imgPlay forState:UIControlStateNormal];
	
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerStateDidChange:) name:@"ASStatusChangedNotification" object:nil];

	return self;
}

- (void)playerStateDidChange:(NSNotification *)notification;
{
	NSLog(@"as, state:%d", player.state);
//	[player isWaiting] ? [self.loadingIndicator startAnimating] : [self.loadingIndicator stopAnimating];
	[UIApplication sharedApplication].networkActivityIndicatorVisible = [player isWaiting];
}


- (void) dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver: self];
	btnPlay = nil;
	btnNext = nil;
	imgPlay = nil;
	imgPause = nil;
	self.playlistView = nil;
	self.player = nil;
	[super dealloc];
}

- (IBAction) playPressed: (id)sender
{
//	[btnPlay setBackgroundImage:(btnPlayState = !btnPlayState) ? imgPlay : imgPause forState:UIControlStateNormal];
	if ([player isPaused] || [player isPlaying]) {
		[self play:nil];
	}
	else {
		[self.playlistView.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:YES scrollPosition:UITableViewScrollPositionNone];

		NXSong *song = [[[NX1GClient shared1GClient] playList] objectAtIndex: 0];	
		[self play:[song urlArray]];
	}

}

- (IBAction) nextPressed: (id)sender
{
    [[NSNotificationCenter defaultCenter] postNotificationName:@"kPlayNext" object:nil];
}


- (void) play: (NSArray*) urls
{	
	if ([urls count])
	{
		[player stop];
		self.player = [[[AudioStreamer alloc] initWithURLs:urls] autorelease];
		[player start];
	}
	else 
	{
		[player pause];	// pause will handle play/pause
	}
	
}


@end
