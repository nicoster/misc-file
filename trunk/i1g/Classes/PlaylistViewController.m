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

#define TABS [@"Playlist Search Setting" componentsSeparatedByString:@" "]
//#define MAINLABEL	((UILabel *)self.navigationItem.titleView)

static PlaylistViewController* sharedPlaylistViewController = nil;

@interface PlaylistViewController()


@property (nonatomic, assign, readonly) NX1GClient* httpClient;
@end


@implementation PlaylistViewController
@synthesize playCtrl;

+ (PlaylistViewController*) sharedPlaylistViewCtrlr
{
	return sharedPlaylistViewController;
}

- (void)songDidLoad:(NSNotification *)notification;
{
	if (hidListNext) {
		hidListNext = 0;
	}
	
	[self.tableView reloadData];
}

- (NX1GClient*) httpClient
{
	return [NX1GClient shared1GClient];
}

- (void) loadView
{
	[super loadView];
	
	NSAssert(sharedPlaylistViewController == nil, @"sharedPlaylistViewController isn't nil!");
	sharedPlaylistViewController = self;
	[sharedPlaylistViewController retain];
	
	//	self.navigationItem.titleView = [[[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, 200.0f, 30.0f)] autorelease];
	//	[MAINLABEL setBackgroundColor:[UIColor clearColor]];
	//	[MAINLABEL setTextColor:[UIColor whiteColor]];
	////	[MAINLABEL setFont: [UIFont fontWithName:@"Helvetica" size:19.0]];
	//	[MAINLABEL setTextAlignment:UITextAlignmentCenter];
	
	self.playCtrl = [[PlayController alloc] initWithPlaylistView: self];
	
//	[[[NSBundle mainBundle] loadNibNamed:@"PlayCtrl" owner:self.playCtrl options:nil] lastObject];
	self.navigationItem.titleView = playCtrl.view;
	[playCtrl.view setBackgroundColor: [UIColor clearColor]];
		
	hidListNext = 0;
	[self.httpClient songsByType: SLT_GIVEN withCriteria: nil];
}

- (void) viewDidLoad
{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(songDidLoad:) name:@"kSongDidLoad" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playerStateDidChange:) name:@"ASStatusChangedNotification" object:nil];
	
}


- (NSInteger)tableView:(UITableView *)aTableView numberOfRowsInSection:(NSInteger)section 
{
	return [[self.httpClient playList] count];
}

- (UITableViewCell *)tableView:(UITableView *)tView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	UITableViewCellStyle style =  UITableViewCellStyleDefault;
	UITableViewCell *cell = [tView dequeueReusableCellWithIdentifier:@"BaseCell"];
	if (!cell) 
		cell = [[[UITableViewCell alloc] initWithStyle:style reuseIdentifier:@"BaseCell"] autorelease];
	NXSong *song = [[self.httpClient playList] objectAtIndex: indexPath.row];
	cell.textLabel.text = [song title];
	cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
	cell.editingAccessoryType = UITableViewCellAccessoryNone;
	
	
	return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
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
	if (playCtrl.player.state == AS_STOPPED || playCtrl.player.state == AS_INITIALIZED) 
	{
		if ([self.httpClient.playList count]) {
			[self.httpClient.history addObject: [self.httpClient.playList objectAtIndex:0]];
		}
			
		[self performSelector:@selector(playNext) withObject: nil afterDelay: 1];
	}
	else {
		[NSObject cancelPreviousPerformRequestsWithTarget: self selector:@selector(playNext) object:nil];
	}
	
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath 
{
	NXSong *song = [[self.httpClient playList] objectAtIndex: indexPath.row];
	
	//	[MAINLABEL setText:song.title];
		
	[playCtrl play:[song urlArray]];
	
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
	self.playCtrl = nil;
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
    [self becomeFirstResponder];
}

- (void)viewWillDisappear:(BOOL)animated {
    [self resignFirstResponder];
    [super viewWillDisappear:animated];
}
@end

