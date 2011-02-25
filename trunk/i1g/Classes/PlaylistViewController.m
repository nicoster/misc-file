//
//  PlaylistViewController.m
//  i1G
//
//  Created by Nick Xiao on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlaylistViewController.h"
#import "i1GAppDelegate.h"
#import "NX1GClient.h"
#import "AudioStreamer.h"
#import "PlayController.h"

#define TABS [@"Playlist Search Setting" componentsSeparatedByString:@" "]
//#define MAINLABEL	((UILabel *)self.navigationItem.titleView)

@interface PlaylistViewController()

@property (nonatomic, retain, readwrite) PlayController* playCtrl;
@end


@implementation PlaylistViewController
@synthesize player, playCtrl;

- (void)songDidLoad:(NSNotification *)notification;
{
	[self.tableView reloadData];
}

- (void) loadView
{
	[super loadView];
	//	self.navigationItem.titleView = [[[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, 200.0f, 30.0f)] autorelease];
	//	[MAINLABEL setBackgroundColor:[UIColor clearColor]];
	//	[MAINLABEL setTextColor:[UIColor whiteColor]];
	////	[MAINLABEL setFont: [UIFont fontWithName:@"Helvetica" size:19.0]];
	//	[MAINLABEL setTextAlignment:UITextAlignmentCenter];
	
	self.playCtrl = [[PlayController alloc] initWithPlaylistView: self];
	
	[[[NSBundle mainBundle] loadNibNamed:@"navtitle" owner:self.playCtrl options:nil] lastObject];
	self.navigationItem.titleView = playCtrl.view;
	[playCtrl.view setBackgroundColor: [UIColor clearColor]];
	
	
	[[NX1GClient shared1GClient] listSongsByType: SLT_GIVEN];
}

- (void) viewDidLoad
{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(songDidLoad:) name:@"SONG_LOADED" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerStateDidChange:) name:@"ASStatusChangedNotification" object:nil];
	
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

- (void) playNext
{
	[self.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:1 inSection:0] animated:YES scrollPosition:UITableViewScrollPositionNone];
	[self tableView: self.tableView didSelectRowAtIndexPath: [NSIndexPath indexPathForRow:1 inSection:0]];
	
}


- (NSInteger)tableView:(UITableView *)aTableView numberOfRowsInSection:(NSInteger)section 
{
	return [[[NX1GClient shared1GClient] playList] count];
}

- (UITableViewCell *)tableView:(UITableView *)tView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	UITableViewCellStyle style =  UITableViewCellStyleDefault;
	UITableViewCell *cell = [tView dequeueReusableCellWithIdentifier:@"BaseCell"];
	if (!cell) 
		cell = [[[UITableViewCell alloc] initWithStyle:style reuseIdentifier:@"BaseCell"] autorelease];
	NXSong *song = [[[NX1GClient shared1GClient] playList] objectAtIndex: indexPath.row];
	cell.textLabel.text = [song title];
	cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
	cell.editingAccessoryType = UITableViewCellAccessoryNone;
	
	
	return cell;
}

// Respond to accessory button taps
-(void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath
{
	//	[self.tableView reloadData];
	CGContextRef context = UIGraphicsGetCurrentContext();
	[UIView beginAnimations:nil context:context];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
	[UIView setAnimationDuration:1.0];
	
	UIView *whiteBackdrop = self.view;//[self.view viewWithTag:100];
	
	[UIView setAnimationTransition: UIViewAnimationTransitionFlipFromLeft forView:whiteBackdrop cache:YES];
	//	NSInteger purple = [[whiteBackdrop subviews] indexOfObject:[whiteBackdrop viewWithTag:999]];
	//	NSInteger maroon = [[whiteBackdrop subviews] indexOfObject:[whiteBackdrop viewWithTag:998]];
	//	[whiteBackdrop exchangeSubviewAtIndex:purple withSubviewAtIndex:maroon];
	//	
	//	[UIView setAnimationDelegate:self];
	[UIView setAnimationDidStopSelector:@selector(animationFinished:)];
	[UIView commitAnimations];	
	
}

- (void)playerStateDidChange:(NSNotification *)notification;
{
	if (player.state == AS_STOPPED || player.state == AS_INITIALIZED) 
	{
		[self performSelector:@selector(playNext) withObject: nil afterDelay: 1];
	}
	else {
		[NSObject cancelPreviousPerformRequestsWithTarget: self selector:@selector(playNext) object:nil];
	}
	
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath 
{
	NXSong *song = [[[NX1GClient shared1GClient] playList] objectAtIndex: indexPath.row];
	
	//	[MAINLABEL setText:song.title];
	
	NSString *url = [[song.urls objectAtIndex:0] url];		
	NSLog(@"as, song:%@", url);	
	
	[self play:url];
	
	if (indexPath.row) {
		NSRange range = NSMakeRange(0, indexPath.row);
		[[[NX1GClient shared1GClient] playList] removeObjectsInRange: range];
		[[[NX1GClient shared1GClient] playList] addObjectsFromArray: [[[NX1GClient shared1GClient] songs] subarrayWithRange: range]];
		[[[NX1GClient shared1GClient] songs] removeObjectsInRange: range];
		NSMutableArray *cellsToDelete = [NSMutableArray arrayWithCapacity:indexPath.row];
		for (int i = 0; i < indexPath.row; i++) {
			[cellsToDelete addObject: [NSIndexPath indexPathForRow: i inSection: indexPath.section]];
		}
		NSMutableArray *cellsToInsert = [NSMutableArray arrayWithCapacity:indexPath.row];
		for (int i = 0; i < indexPath.row; i++) {
			[cellsToInsert addObject: [NSIndexPath indexPathForRow: [[[NX1GClient shared1GClient] playList] count] - indexPath.row + i inSection: indexPath.section]];
		}
		
		
		
		
		//filtering animation and presentation model update
		[self.tableView beginUpdates];
		{
			[self.tableView deleteRowsAtIndexPaths:cellsToDelete withRowAnimation:UITableViewRowAnimationTop];
			[self.tableView insertRowsAtIndexPaths:cellsToInsert withRowAnimation:UITableViewRowAnimationBottom];
		}
		[self.tableView endUpdates];		
	}	
}

- (void) dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	self.playCtrl = nil;
	self.player = nil;
	[super dealloc];
}

@end

