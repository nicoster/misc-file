//
//  SearchResultViewController.m
//  i1G
//
//  Created by Nick Xiao on 2/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "SearchResultViewController.h"
#import "NX1GClient.h"
#import "PlaylistViewController.h"
#import "PlayController.h"
#import "PlaylistCell.h"
#import "i1GAppDelegate.h"

@interface SearchResultViewController()

@property (nonatomic, retain) UISearchBar *searchBar;
@property (nonatomic, assign, readonly) NX1GClient* httpClient;
- (void)searchDidFinish:(NSNotification *)notification;


@end


@implementation SearchResultViewController

@synthesize searchBar, searchContainer;

- (void)dealloc {
	hidSearch = 0;
	self.searchBar = nil;
	self.searchContainer = nil;
    [super dealloc];
}

- (NX1GClient*) httpClient
{
	return [NX1GClient shared1GClient];
}

#pragma mark -
#pragma mark View lifecycle

- (void)viewDidLoad {
	[super viewDidLoad];
	[searchContainer.view addSubview:self.view];
	self.view.frame = CGRectMake(0, 0, 320, 460);

	hidSearch = 0;

	self.searchBar = [[[UISearchBar alloc] initWithFrame:
						CGRectMake(0.0, 0.0, self.view.bounds.size.width, 44.0)] autorelease];
	 
	 //	searchBar.showsCancelButton = YES;
	 [searchBar setBackgroundColor: [UIColor clearColor]];
	 searchBar.delegate = self;
//	 self.navigationItem.titleView = searchBar;
	self.tableView.tableHeaderView = searchBar;

	NSArray *buttonNames = [NSArray arrayWithObjects:@"我的收藏", @"播放历史", @"手气不错", nil];
	UISegmentedControl* segmentedControl = [[UISegmentedControl alloc] initWithItems:buttonNames];
	segmentedControl.segmentedControlStyle = UISegmentedControlStyleBar; 
	[segmentedControl addTarget:self action:@selector(segmentAction:) forControlEvents:UIControlEventValueChanged];
	segmentedControl.momentary = YES;
	searchContainer.navigationItem.titleView = segmentedControl;	
	
	
//	UISearchDisplayController *searchDC = nil;
//	searchDC = [[UISearchDisplayController alloc] initWithSearchBar:self.searchBar contentsController:self];
//	searchDC.searchResultsDataSource = self;
//	searchDC.searchResultsDelegate = self;
	
	 [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(searchDidFinish:) name:@"kSearchDidFinish" object:nil];
}
 

-(void) segmentAction: (UISegmentedControl *) sender
{
	// Update the label with the segment number
//	[label setText:[NSString stringWithFormat:@"%0d", sender.selectedSegmentIndex + 1]];
	switch (sender.selectedSegmentIndex) {
		case 0:
		{
			[searchBar resignFirstResponder];
			searchBar.text = [NSString stringWithFormat: @"@%@", [[NSUserDefaults standardUserDefaults] stringForKey:@"kPreferenceUser"]];
			hidSearch = [[NX1GClient shared1GClient] songsByType:SLT_SEARCH withCriteria: searchBar.text];
			[self.tableView reloadData];
			break;
		}
		case 1:
		{
			[NX1GClient shared1GClient].searchResults = [NX1GClient shared1GClient].history;
			[[NSNotificationCenter defaultCenter] postNotificationName:@"kSearchDidFinish" object:nil];
			break;
		}
		default:
			break;
	}
}

/*
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}
*/
/*
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}
*/
/*
- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}
*/
/*
- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
}
*/
/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

#pragma mark -

- (void)searchDidFinish:(NSNotification *)notification;
{
	hidSearch = 0;

	[self.tableView reloadData];
}


#pragma mark -
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	if (hidSearch) {
		return 1;
	}
	
    // Return the number of rows in the section.
    return [[[NX1GClient shared1GClient] searchResults] count];
}


// Customize the appearance of table view cells.
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	if (hidSearch) {
		return 500.f;
	}
	return 48.0f;
}	

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

	PlaylistCell *cell = (PlaylistCell*)[tableView dequeueReusableCellWithIdentifier:@"SearchResultCell"];
	if (!cell) 
	{
		cell = [[[NSBundle mainBundle] loadNibNamed:@"PlaylistCell" owner:self options:nil] lastObject];
		cell.reuseIdentifier = @"SearchResultCell";
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
	}
	
	[cell updatePlayProgress:NO];
	
	if (hidSearch) {
		cell.title.alpha = 0.7;
		cell.btnAdd.hidden = YES;
		cell.title.textAlignment = UITextAlignmentCenter;
		cell.title.text = @"Searching..";
		
		cell.subtitle.text = @"";
		cell.accessoryType = UITableViewCellAccessoryNone;
	}
	else {
		cell.title.alpha = 1;
		cell.btnAdd.hidden = NO;
		cell.title.textAlignment = UITextAlignmentLeft;
		NXSong *song = [[[NX1GClient shared1GClient] searchResults] objectAtIndex: indexPath.row];
		cell.title.text = [song title];
		cell.subtitle.text = [NSString stringWithFormat:@"%@ - %@", [song singer], [song album]];;
		
	}

	
    return cell;
}


/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/


/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source.
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
    }   
}
*/


/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/


/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/


#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    // Navigation logic may go here. Create and push another view controller.
    /*
    <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
    // ...
    // Pass the selected object to the new view controller.
    [self.navigationController pushViewController:detailViewController animated:YES];
    [detailViewController release];
    */
	
	NXSong *song = [[self.httpClient searchResults] objectAtIndex: indexPath.row];
	
	[self.httpClient.playList insertObject: song atIndex: [self.httpClient.playList count] ? 1 : 0];
	
	[self.httpClient saveGivenIds];
	
	[[[PlaylistViewController sharedPlaylistViewCtrlr] tableView] reloadData];
	[[PlaylistViewController sharedPlaylistViewCtrlr] playNext];
//	[[i1GAppDelegate sharedAppDelegate] forView:self.view showPrompt:@"开始播放 %@ - %@", song.title, song.singer];
	
}

#pragma mark -
#pragma mark UISearchBarDelegate

// called when keyboard search button pressed
- (void)searchBarSearchButtonClicked:(UISearchBar *)theSearchBar
{
	[self.searchBar resignFirstResponder];
	
	hidSearch = [[NX1GClient shared1GClient] songsByType:SLT_SEARCH withCriteria:theSearchBar.text];
	[self.tableView reloadData];
}

// called when cancel button pressed
- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar
{
	[self.searchBar resignFirstResponder];
}

- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar                     // called when text starts editing
{
//	[UIView beginAnimations:nil context:nil];
	self.searchBar.showsCancelButton = YES;
//	[UIView commitAnimations];
	
}
- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar                      // called when text ends editing
{
	self.searchBar.showsCancelButton = NO;
}


#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
	[super viewDidUnload];
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	
	// release and set to nil
	self.searchBar = nil;

}



@end

