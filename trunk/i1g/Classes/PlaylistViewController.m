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
#import "SongDetailViewController.h"
#import "PlaylistCell.h"

#define TABS [@"Playlist Search Setting" componentsSeparatedByString:@" "]
//#define MAINLABEL	((UILabel *)self.navigationItem.titleView)

static PlaylistViewController* sharedPlaylistViewController = nil;

@interface PlaylistViewController()

- (IBAction) playPressed: (id)sender;
- (IBAction) nextPressed: (id)sender;

@property (nonatomic, assign, readonly) NX1GClient* httpClient;
@end


@implementation PlaylistViewController
//@synthesize playCtrl;
@synthesize player;

+ (PlaylistViewController*) sharedPlaylistViewCtrlr
{
	return sharedPlaylistViewController;
}

- (void)songDidLoad:(NSNotification *)notification;
{
	if (hidListNext) {
		hidListNext = 0;
	}
	
	[overlay removeFromSuperview];
	[overlay release];
	overlay = nil;
	
	[self.tableView reloadData];
	[self tableView: self.tableView didSelectRowAtIndexPath: [NSIndexPath indexPathForRow:0 inSection:0]];

}

- (NX1GClient*) httpClient
{
	return [NX1GClient shared1GClient];
}


- (void) viewDidLoad
{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(songDidLoad:) name:@"kSongDidLoad" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerStateDidChange:) name:@"ASStatusChangedNotification" object:nil];
	
	NSAssert(sharedPlaylistViewController == nil, @"sharedPlaylistViewController isn't nil!");
	sharedPlaylistViewController = self;
	[sharedPlaylistViewController retain];
		
//	self.playCtrl = [[PlayController alloc] initWithPlaylistView: self];	
	//	[playCtrl.view setBackgroundColor: [UIColor clearColor]];
	//	self.navigationItem.titleView = playCtrl.view;
//	[self.view addSubview: playCtrl.view];

	self.view.frame = CGRectMake(0, 0, 320, 416);
	// build a toolbar
	{
		UIToolbar *tb = [[UIToolbar alloc] initWithFrame:CGRectMake(0.0f, 372.0f, 320.0f, 44.0f)];
		NSMutableArray *tbitems = [NSMutableArray array];
		
		UIBarButtonItem *bbi = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:nil] autorelease];
		bbi.width = 120.0f;
		[tbitems addObject:bbi];
		[tbitems addObject:SYSBARBUTTON(UIBarButtonSystemItemPlay, @selector(playPressed:))];
//		bbi = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:nil] autorelease];
//		bbi.width = 20.0f;
//		[tbitems addObject:bbi];
//		[tbitems addObject:SYSBARBUTTON(UIBarButtonSystemItemPause, @selector(playPressed:))];
		bbi = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:nil] autorelease];
		bbi.width = 20.0f;
		[tbitems addObject:bbi];
		[tbitems addObject:SYSBARBUTTON(UIBarButtonSystemItemFastForward, @selector(nextPressed:))];
		
		tb.items = tbitems;
		
		[mainView addSubview: self.view];
		[mainView addSubview: tb];
		[mainView addSubview: overlay];
	}
	
	
	hidListNext = 0;
	[self.httpClient songsByType: SLT_GIVEN withCriteria: nil];
}


- (NSInteger)tableView:(UITableView *)aTableView numberOfRowsInSection:(NSInteger)section 
{
	return [[self.httpClient playList] count];
}

- (UITableViewCell *)tableView:(UITableView *)tView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
//	UITableViewCellStyle style =  UITableViewCellStyleDefault;
	PlaylistCell *cell = (PlaylistCell*)[tView dequeueReusableCellWithIdentifier:@"PlaylistCell"];
//	if (!cell) 
//		cell = [[[PlaylistCell alloc] initWithStyle:style reuseIdentifier:@"BaseCell"] autorelease];
	if (!cell) 
	{
		cell = [[[NSBundle mainBundle] loadNibNamed:@"PlaylistCell" owner:self options:nil] lastObject];
		cell.reuseIdentifier = @"PlaylistCell";
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
	}
	
	[cell updatePlayProgress:NO];
	
	NXSong *song = [[self.httpClient playList] objectAtIndex: indexPath.row];
	cell.title.text = [song title];
	cell.subtitle.text = [NSString stringWithFormat:@"%@ - %@", [song singer], [song album]];
//	cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
//	cell.editingAccessoryType = UITableViewCellAccessoryNone;

	
	return (UITableViewCell*)cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 48.0f;
	if (indexPath.row == 0) {
		return 60.0f;
	}
	else {
		return 44.0f;
	}

	
}


// Respond to accessory button taps
-(void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath
{

	SongDetailViewController *detailview = [[[SongDetailViewController alloc] initWithIndexPath: indexPath] autorelease];
//	[[[NSBundle mainBundle] loadNibNamed:@"SongDetailView" owner:detailview options:nil] lastObject];
	[self.navigationController pushViewController:detailview animated:YES];
	
	/*
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
	*/
}

- (void)playerStateDidChange:(NSNotification *)notification;
{
	if (self.player.state == AS_STOPPED || self.player.state == AS_INITIALIZED) 
	{
		if ([self.httpClient.playList count]) {
			[self.httpClient.history addObject: [self.httpClient.playList objectAtIndex:0]];
		}
			
		[self performSelector:@selector(playNext) withObject: nil afterDelay: 1];
	}
	else {
		[NSObject cancelPreviousPerformRequestsWithTarget: self selector:@selector(playNext) object:nil];
	}
	
	[UIApplication sharedApplication].networkActivityIndicatorVisible = [player isWaiting];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath 
{
	
	NXSong *song = [[self.httpClient playList] objectAtIndex: indexPath.row];
	
	
	
	if (self.player.progress > 60) {
		NXSong *playing = [[self.httpClient playList] objectAtIndex: 0];
		if (playing) {
			if (self.httpClient.history) {
				[self.httpClient.history addObject:playing];
			} else {
				self.httpClient.history = [NSMutableArray arrayWithObject:playing];
			}

		}
	}
		
	[self play:[song urlArray]];
	
	[[i1GAppDelegate sharedAppDelegate] forView:self.view.superview showPrompt:@"开始播放 %@ - %@", song.title, song.singer];
	
	PlaylistCell *cell = (PlaylistCell*)[tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0]];
	[cell updatePlayProgress:NO];
	
	cell = (PlaylistCell*)[tableView cellForRowAtIndexPath:indexPath];
	[cell updatePlayProgress:YES];
	
	// animation for remove/append items
	if (indexPath.row) {
		[[self.httpClient playList] removeObjectsInRange: NSMakeRange(0, indexPath.row)];
		
		int insertCount = indexPath.row;
		
		if (indexPath.row > [self.httpClient.songs count]) {
			insertCount = [self.httpClient.songs count];
			[self.httpClient.playList addObjectsFromArray:self.httpClient.songs];
			[self.httpClient.songs removeAllObjects];
		}
		else {
			NSRange range = NSMakeRange(0, indexPath.row);
			[[self.httpClient playList] addObjectsFromArray: [[self.httpClient songs] subarrayWithRange: range]];
			[[self.httpClient songs] removeObjectsInRange: range];
		}
		[self.httpClient saveGivenIds];

		NSMutableArray *cellsToDelete = [NSMutableArray arrayWithCapacity:indexPath.row];
		for (int i = 0; i < indexPath.row; i++) {
			[cellsToDelete addObject: [NSIndexPath indexPathForRow: i inSection: indexPath.section]];
		}
		NSMutableArray *cellsToInsert = [NSMutableArray arrayWithCapacity:insertCount];
		for (int i = 0; i < insertCount; i++) {
			[cellsToInsert addObject: [NSIndexPath indexPathForRow: [[self.httpClient playList] count] - indexPath.row + i inSection: indexPath.section]];
		}
		
		//filtering animation and presentation model update
		[self.tableView beginUpdates];
		{
			[self.tableView deleteRowsAtIndexPaths:cellsToDelete withRowAnimation:UITableViewRowAnimationTop];
			[self.tableView insertRowsAtIndexPaths:cellsToInsert withRowAnimation:UITableViewRowAnimationBottom];

		}
		[self.tableView endUpdates];
		[self.tableView scrollToNearestSelectedRowAtScrollPosition:UITableViewScrollPositionTop animated:YES];
		
		NSLog(@"pl, songs:%d", [[self.httpClient songs] count]);
		
	}
	
	if (hidListNext == 0 && [[self.httpClient songs] count] < PLAYLISTSIZE) {
		hidListNext = [self.httpClient songsByType:SLT_NEXT withCriteria:nil];
	}
}

- (IBAction) playPressed: (id)sender
{
	if ([player isPaused] || [player isPlaying]) {
		[self play:nil];
	}
	else {
		[self.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:YES scrollPosition:UITableViewScrollPositionNone];
		
		NXSong *song = [[[NX1GClient shared1GClient] playList] objectAtIndex: 0];	
		[self play:[song urlArray]];
	}
	
}

- (IBAction) nextPressed: (id)sender
{
	[self playNext];
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

- (void) playNext
{
	if ([self.httpClient.playList count] > 1) {
		[self.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:1 inSection:0] animated:YES scrollPosition:UITableViewScrollPositionNone];
		[self tableView: self.tableView didSelectRowAtIndexPath: [NSIndexPath indexPathForRow:1 inSection:0]];
	}
	else {
		NSLog(@"pl, cannot play next as there's no more");
	}

}

- (void) dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
//	self.playCtrl = nil;
	[sharedPlaylistViewController release];
	sharedPlaylistViewController = nil;
	[super dealloc];
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (motion == UIEventSubtypeMotionShake)
    {
        NSLog(@"Shaking..");
		[self playNext];
    }
}

-(BOOL)canBecomeFirstResponder {
    return YES;
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
	UIApplication *application = [UIApplication sharedApplication];
	if([application respondsToSelector:@selector(beginReceivingRemoteControlEvents)])
		[application beginReceivingRemoteControlEvents];
    [self becomeFirstResponder];
}

- (void)viewWillDisappear:(BOOL)animated {
    [self resignFirstResponder];
    [super viewWillDisappear:animated];
}

#pragma mark Remote Control Events
/* The iPod controls will send these events when the app is in the background */
- (void)remoteControlReceivedWithEvent:(UIEvent *)event {
	switch (event.subtype) {
		case UIEventSubtypeRemoteControlTogglePlayPause:
			[self.player pause];
			break;
		case UIEventSubtypeRemoteControlPlay:
			[self.player start];
			break;
		case UIEventSubtypeRemoteControlPause:
			[self.player pause];
			break;
		case UIEventSubtypeRemoteControlStop:
			[self.player stop];
			break;
		default:
			break;
	}
}

@end

