//
//  WeatherDetailsController.m
//  wirelessDemo
//
//  Created by Nick Xiao on 1/2/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "WeatherDetailsController.h"
#import "WeatherCell.h"

#define SEPARATOR_COLOR [UIColor colorWithRed:0.1266 green:0.2633 blue:0.3882 alpha:1.0f]
#define TITLE_COLOR [UIColor colorWithRed:0.1686 green:0.2275 blue:0.3333 alpha:1.0f]
#define ITEM_COLOR [UIColor colorWithRed:0.2392 green:0.3373 blue:0.4784 alpha:1.0f]


@implementation WeatherDetailsController


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

//- (void) loadView
//{
//    GraphView *aGraphView = [[GraphView alloc] initWithFrame:CGRectZero];
//    aGraphView.backgroundColor = [UIColor whiteColor];
//    self.view = aGraphView;
//    self.graphView = aGraphView;
//    
//    [aGraphView release];    
//}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    UITableView *view = (UITableView*)self.view;

    view.frame = CGRectMake(20, 154, 280, 178);
    view.autoresizingMask = UIViewAutoresizingNone;
    view.backgroundColor = TITLE_COLOR;
    view.separatorColor = SEPARATOR_COLOR;
    view.showsHorizontalScrollIndicator = NO;
    view.showsVerticalScrollIndicator = NO;
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section 
{
    return 5;
}

- (NSString *)getDayOfTheWeek:(NSDate *)date
{
    NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init] autorelease];
    [dateFormatter setDateFormat: @"EEEE"];
    NSString *formattedDateString = [dateFormatter stringFromDate:date];
    return formattedDateString;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    WeatherCell* cell = (WeatherCell*) [tableView dequeueReusableCellWithIdentifier: @"WeatherCell"];
    if (! cell)
    {
		cell = [[[NSBundle mainBundle] loadNibNamed:@"WeatherCell" owner:self options:nil] lastObject];
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    
    cell.weekDay.text = [self getDayOfTheWeek: [NSDate dateWithTimeIntervalSinceNow:60 * 60 * 24 * indexPath.row]];
    int high = arc4random() % 20 + 1;
    int low = arc4random() % high;
    cell.tempHigh.text = [NSString stringWithFormat: @"%d°", high];
    cell.tempLow.text = [NSString stringWithFormat: @"%d°", low];
    cell.backgroundColor = [UIColor blueColor];
//	cell.backgroundColor = (indexPath.row % 2 ? ITEM_COLOR : TITLE_COLOR);
    
	return (UITableViewCell*)cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 36.0f;	
}
/*

// Respond to accessory button taps
-(void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath
{
    
	SongDetailViewController *detailview = [[[SongDetailViewController alloc] initWithIndexPath: indexPath] autorelease];
    //	[[[NSBundle mainBundle] loadNibNamed:@"SongDetailView" owner:detailview options:nil] lastObject];
	[self.navigationController pushViewController:detailview animated:YES];
	
}

- (void)removeCells: (NSRange) range
{
	if (range.length == 0) {
		return;
	}
    //	NSMutableArray *pl = self.i1gClient.playList;
	NSAssert(range.location + range.length <= self.i1gClient.playList.count, @"invalid range for removing playlist");
	// animation for remove/append items
	if (range.length) {
		[[self.i1gClient playList] removeObjectsInRange: range];
		
		NSMutableArray *cellsToDelete = [NSMutableArray arrayWithCapacity:range.length];
		for (int i = range.location; i < range.location + range.length; i++) {
			[cellsToDelete addObject: [NSIndexPath indexPathForRow: i inSection: 0]];
		}	
		
		int insertCount = range.length;		
		if (insertCount > [self.i1gClient.songs count]) {
			insertCount = [self.i1gClient.songs count];
			[self.i1gClient.playList addObjectsFromArray:self.i1gClient.songs];
			[self.i1gClient.songs removeAllObjects];
		}
		else {
			range.location = 0;
			[[self.i1gClient playList] addObjectsFromArray: [[self.i1gClient songs] subarrayWithRange: range]];
			[[self.i1gClient songs] removeObjectsInRange: range];
		}
		[self.i1gClient saveGivenIds];
		
		NSMutableArray *cellsToInsert = [NSMutableArray arrayWithCapacity:insertCount];
		for (int i = 0; i < insertCount; i++) {
			[cellsToInsert addObject: [NSIndexPath indexPathForRow: [[self.i1gClient playList] count] - range.length + i inSection: 0]];
		}
		
		//filtering animation and presentation model update
		[self.tableView beginUpdates];
		{
			[self.tableView deleteRowsAtIndexPaths:cellsToDelete withRowAnimation:UITableViewRowAnimationFade];
			[self.tableView insertRowsAtIndexPaths:cellsToInsert withRowAnimation:UITableViewRowAnimationFade];
			
		}
		[self.tableView endUpdates];
        //		[self.tableView scrollToNearestSelectedRowAtScrollPosition:UITableViewScrollPositionTop animated:YES];
		
		NSLog(@"pl, songs:%d", [[self.i1gClient songs] count]);
		
	}
	
	if (hidListNext == 0 && [[self.i1gClient songs] count] < PLAYLISTSIZE) {
		hidListNext = [self.i1gClient songsByType:SLT_NEXT withCriteria:nil];
	}
	
}


- (void)tableView:(UITableView *)aTableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath 
{
	[self removeCells:NSMakeRange(indexPath.row, 1)];
	
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath 
{
	
	NXSong *song = [[self.i1gClient playList] objectAtIndex: indexPath.row];
	
	if (self.player.progress > 6) {
		NXSong *playing = [[self.i1gClient playList] objectAtIndex: 0];
		if (playing) {
			if (self.i1gClient.history) {
				[self.i1gClient.history addObject:playing];
			} else {
				self.i1gClient.history = [NSMutableArray arrayWithObject:playing];
			}
			NSLog(@"pl, add history:%@, %d, count:%d", playing.title, (int)self.player.progress, self.i1gClient.history.count);
			
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

*/
@end
