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

@interface SearchResultViewController()

@property (nonatomic, retain) UISearchBar *searchBar;
@property (nonatomic, assign, readonly) NX1GClient* httpClient;
- (void)searchDidFinish:(NSNotification *)notification;


@end


@implementation SearchResultViewController

@synthesize searchBar;

- (NX1GClient*) httpClient
{
	return [NX1GClient shared1GClient];
}

#pragma mark -
#pragma mark View lifecycle

- (void) loadView
{
	[super loadView];
	
	self.searchBar = [[[UISearchBar alloc] initWithFrame:
					   CGRectMake(0.0, 0.0, self.view.bounds.size.width, 44.0)] autorelease];
	
//	searchBar.showsCancelButton = YES;
	[searchBar setBackgroundColor: [UIColor clearColor]];
	searchBar.delegate = self;
	self.navigationItem.titleView = searchBar;

	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(searchDidFinish:) name:@"kSearchDidFinish" object:nil];
}

/*
- (void)viewDidLoad {
    [super viewDidLoad];

    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}
*/

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
	[self.tableView reloadData];
}


#pragma mark -
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    // Return the number of rows in the section.
    return [[[NX1GClient shared1GClient] searchResults] count];
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
 	NXSong *song = [[[NX1GClient shared1GClient] searchResults] objectAtIndex: indexPath.row];
	cell.textLabel.text = [song title];
	cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
	cell.editingAccessoryType = UITableViewCellAccessoryNone;
	
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
	
	[self.httpClient.playList insertObject: song atIndex: 0];
	
	[self.httpClient saveGivenIds];
	
	[[[PlaylistViewController sharedPlaylistViewCtrlr] tableView] reloadData];
	[[PlaylistViewController sharedPlaylistViewCtrlr].playCtrl play:[song urlArray]];
	
}

#pragma mark -
#pragma mark UISearchBarDelegate

// called when keyboard search button pressed
- (void)searchBarSearchButtonClicked:(UISearchBar *)theSearchBar
{
	[self.searchBar resignFirstResponder];
	
	[[NX1GClient shared1GClient] songsByType:SLT_SEARCH withCriteria:theSearchBar.text];
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


- (void)dealloc {
	self.searchBar = nil;
    [super dealloc];
}


@end

