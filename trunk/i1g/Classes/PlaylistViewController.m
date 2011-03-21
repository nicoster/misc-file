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

//static PlaylistViewController* sharedPlaylistViewController = nil;

@interface PlaylistViewController()

- (IBAction) playPressed: (id)sender;
- (IBAction) nextPressed: (id)sender;
- (void) playNext;
- (void) play: (NSArray*) urls;
- (void) handlePlayNotification: (NSNotification*) note;

@property (nonatomic, assign, readonly) NX1GClient* httpClient;
@end


@implementation PlaylistViewController
//@synthesize playCtrl;
@synthesize player, container;

- (id) initWithContainer: (UIViewController*) aContainer
{
	self = [super init];
	self.container = aContainer;
	return self;
}

- (void) dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
//	self.playCtrl = nil;
    self.container = nil;

	[super dealloc];
}

- (void)songDidLoad:(NSNotification *)notification;
{
	if (hidListNext) {
		hidListNext = 0;
	}
	
	[[i1GAppDelegate sharedAppDelegate].overlay removeFromSuperview];
	
	[self.tableView reloadData];
	[self tableView: self.tableView didSelectRowAtIndexPath: [NSIndexPath indexPathForRow:0 inSection:0]];

}

- (void)favDidLoad: (NSNotification*) note
{
	[self.tableView reloadData];
}

- (void)reloadPlaylist: (NSNotification*) note
{
    [self.tableView reloadData];
}

- (NX1GClient*) httpClient
{
	return [NX1GClient shared1GClient];
}

- (void) startPlayer: (NSNotification*) note
{
    [self.player start];
}

- (void) stopPlayer: (NSNotification*) note
{
    [self.player stop];
}

- (void) pausePlayer: (NSNotification*) note
{
    [self.player pause];
}

- (void) viewDidLoad
{
	NSLog(@"perf, pl, viewDidLoad");
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(songDidLoad:) name:@"kSongDidLoad" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(favDidLoad:) name:@"kFavDidLoad" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerStateDidChange:) name:@"ASStatusChangedNotification" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handlePlayNotification:) name:@"kPlaySong" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playNext) name:@"kPlayNext" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadPlaylist:) name:@"kReloadPlaylist" object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(startPlayer:) name:@"kStartPlayer" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stopPlayer:) name:@"kStopPlayer" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(pausePlayer:) name:@"kPausePlayer" object:nil];
			
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
		
		[container.view addSubview: self.view];
		[container.view addSubview: tb];
		[container.view addSubview: [i1GAppDelegate sharedAppDelegate].overlay];
	}
	
	
	hidListNext = 0;
	

	[self.httpClient songsByType: SLT_GIVEN withCriteria: nil];
}


- (NSInteger)tableView:(UITableView *)aTableView numberOfRowsInSection:(NSInteger)section 
{
//	NSMutableArray *pl = self.httpClient.playList;
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
		cell.selectionStyle = UITableViewCellSelectionStyleGray;
	}
	
	[cell updatePlayProgress:NO];
	
	NXSong *song = [[self.httpClient playList] objectAtIndex: indexPath.row];
	cell.title.text = [song title];
	cell.subtitle.text = [NSString stringWithFormat:@"%@ - %@", [song album], [song singer]];
//	cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
//	cell.editingAccessoryType = UITableViewCellAccessoryNone;
	
    bool isFav = [self.httpClient isFav:song.songId];
	UIImage *img = [UIImage imageNamed:(isFav ? @"fav.png" : @"notfav.png")];
	[cell.btnAdd setBackgroundImage:img forState:UIControlStateNormal];
	cell.btnAdd.alpha = (isFav ? 1 : 0.2);
	
    cell.playlistController = self;
	
	if (indexPath.row == 0) {
		[cell updatePlayProgress:YES];
	}

	
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
		
		[self performSelector:@selector(playNext) withObject: nil afterDelay: 1];
	}
	else {
		[NSObject cancelPreviousPerformRequestsWithTarget: self selector:@selector(playNext) object:nil];
	}
	
	[UIApplication sharedApplication].networkActivityIndicatorVisible = [player isWaiting];
}

- (void)removeCells: (NSRange) range
{
	if (range.length == 0) {
		return;
	}
//	NSMutableArray *pl = self.httpClient.playList;
	NSAssert(range.location + range.length <= self.httpClient.playList.count, @"invalid range for removing playlist");
	// animation for remove/append items
	if (range.length) {
		[[self.httpClient playList] removeObjectsInRange: range];
		
		NSMutableArray *cellsToDelete = [NSMutableArray arrayWithCapacity:range.length];
		for (int i = range.location; i < range.location + range.length; i++) {
			[cellsToDelete addObject: [NSIndexPath indexPathForRow: i inSection: 0]];
		}	
		
		int insertCount = range.length;		
		if (insertCount > [self.httpClient.songs count]) {
			insertCount = [self.httpClient.songs count];
			[self.httpClient.playList addObjectsFromArray:self.httpClient.songs];
			[self.httpClient.songs removeAllObjects];
		}
		else {
			range.location = 0;
			[[self.httpClient playList] addObjectsFromArray: [[self.httpClient songs] subarrayWithRange: range]];
			[[self.httpClient songs] removeObjectsInRange: range];
		}
		[self.httpClient saveGivenIds];
		
		NSMutableArray *cellsToInsert = [NSMutableArray arrayWithCapacity:insertCount];
		for (int i = 0; i < insertCount; i++) {
			[cellsToInsert addObject: [NSIndexPath indexPathForRow: [[self.httpClient playList] count] - range.length + i inSection: 0]];
		}
		
		//filtering animation and presentation model update
		[self.tableView beginUpdates];
		{
			[self.tableView deleteRowsAtIndexPaths:cellsToDelete withRowAnimation:UITableViewRowAnimationFade];
			[self.tableView insertRowsAtIndexPaths:cellsToInsert withRowAnimation:UITableViewRowAnimationFade];
			
		}
		[self.tableView endUpdates];
//		[self.tableView scrollToNearestSelectedRowAtScrollPosition:UITableViewScrollPositionTop animated:YES];
		
		NSLog(@"pl, songs:%d", [[self.httpClient songs] count]);
		
	}
	
	if (hidListNext == 0 && [[self.httpClient songs] count] < PLAYLISTSIZE) {
		hidListNext = [self.httpClient songsByType:SLT_NEXT withCriteria:nil];
	}
	
}


- (void)tableView:(UITableView *)aTableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath 
{
	[self removeCells:NSMakeRange(indexPath.row, 1)];
	
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath 
{
	
	NXSong *song = [[self.httpClient playList] objectAtIndex: indexPath.row];
	
	if (self.player.progress > 6) {
		NXSong *playing = [[self.httpClient playList] objectAtIndex: 0];
		if (playing) {
			if (self.httpClient.history) {
				[self.httpClient.history addObject:playing];
			} else {
				self.httpClient.history = [NSMutableArray arrayWithObject:playing];
			}
			NSLog(@"pl, add history:%@, %d, count:%d", playing.title, (int)self.player.progress, self.httpClient.history.count);
			
		}
	}
	
		
	[self play:[song urlArray]];
	
	[[i1GAppDelegate sharedAppDelegate] forView:nil showPrompt:@"开始播放 %@ - %@", song.title, song.singer];
	
	PlaylistCell *cell = (PlaylistCell*)[tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0]];
	[cell updatePlayProgress:NO];
	
	cell = (PlaylistCell*)[tableView cellForRowAtIndexPath:indexPath];
	[cell updatePlayProgress:YES];
	
	[self removeCells:NSMakeRange(0, indexPath.row)];
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

- (void) handlePlayNotification: (NSNotification*) note
{
    NSArray* urls = [[note userInfo] objectForKey:@"kPlayUrls"];
    [self play: urls];
}

@end

