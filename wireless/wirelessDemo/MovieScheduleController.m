//
//  MovieScheduleController.m
//  wirelessDemo
//
//  Created by Max Qian on 1/6/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "MovieScheduleController.h"
#import <extThree20JSON/extThree20JSON.h>

static NSString* moviescheduleRequestURLPath = @"http://res.88bx.com:8080/wirelesssz/RXService?token=970497ff485736e74c5460416fab0c14&cmd=15&city=320500&movieDay=%d&movieId=%d";

@implementation MovieScheduleController
@synthesize cinematable = _cinematable;

- (id)initwithObj:(NSString*)nibNameOrNil info:(MovieInfo *)p
{
    
    self = [super initWithNibName:nibNameOrNil bundle:nil];
    if (self) {
        _movieinfo = p;
        NSLog(@"name:-- %@",_movieinfo.name_en);
        _cinematable.delegate = self;
    }
    return self;
}

//- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
//{
//    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
//    if (self) {
//        // Custom initialization
//    }
//
//    return self;
//}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
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


#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
#warning Potentially incomplete method implementation.
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
#warning Incomplete method implementation.
    // Return the number of rows in the section.
    return 5;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier] autorelease];
    }
    
    cell.textLabel.text = @"aaaa";
    cell.detailTextLabel.text = @"bbbbb";
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    // Configure the cell...
    
    return cell;
}

/*
 // Override to support conditional editing of the table view.
 - (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
 {
 // Return NO if you do not want the specified item to be editable.
 return YES;
 }
 */

/*
 // Override to support editing the table view.
 - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
 {
 if (editingStyle == UITableViewCellEditingStyleDelete) {
 // Delete the row from the data source
 [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
 }   
 else if (editingStyle == UITableViewCellEditingStyleInsert) {
 // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
 }   
 }
 */

/*
 // Override to support rearranging the table view.
 - (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
 {
 }
 */

/*
 // Override to support conditional rearranging of the table view.
 - (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
 {
 // Return NO if you do not want the item to be re-orderable.
 return YES;
 }
 */

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    /*
     <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
     // ...
     // Pass the selected object to the new view controller.
     [self.navigationController pushViewController:detailViewController animated:YES];
     [detailViewController release];
     */
}

@end

@implementation MovieScheduleDelegate1

- (id)initWithController:(id *)controller {
    //    [super init];
    if (self) {
        _controller = (MovieScheduleController*)controller;
    }
    
    return self;
}


#pragma mark -
#pragma mark TTURLRequestDelegate

///////////////////////////////////////////////////////////////////////////////////////////////////
- (void)requestDidStartLoad:(TTURLRequest*)request {
    //    [_requestButton setTitle:@"Loading..." forState:UIControlStateNormal];
    
}

- (void)request:(TTURLRequest*)request didFailLoadWithError:(NSError*)error {
    
}


///////////////////////////////////////////////////////////////////////////////////////////////////
- (void)requestDidFinishLoad:(TTURLRequest*)request 
{
    TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
    
    NSArray *entries = JsonResponse.rootObject;
    NSLog(@"%d", [entries count]);
    
    for (NSDictionary* entry in entries) {
        NSDictionary *details = [entry objectForKey:@"CinamaInfo"];
        //NSLog(@"entry: %@",entry);
        
        //        CinemaInfo * cinemainfo = [[[CinemaInfo alloc] init]autorelease];
        //        cinemainfo.cinemaid = [NSNumber numberWithInt:[[details objectForKey:@"cinemaId"] integerValue]];
        //        //NSLog(@"moviename: %@", movieinfo.name);
        //        
        //        
        //        cinemainfo.cinemaname = [details objectForKey:@"cinemaName"];
        //        cinemainfo.address = [details objectForKey:@"address"];
        //        cinemainfo.city = [details objectForKey:@"city"];
        //        cinemainfo.area = [details objectForKey:@"area"];
        //        cinemainfo.description = [details objectForKey:@"description"];
        //        
        //        
        //        cinemainfo.imageurl = [details objectForKey:@"imageUrl"];
        //        cinemainfo.logourl = [details objectForKey:@"logoUrl"];
        //        cinemainfo.busline = [details objectForKey:@"bus"];
        //        cinemainfo.telphone = [details objectForKey:@"telphone"];
        //        cinemainfo.opentime = [details objectForKey:@"opentime"];
        //        cinemainfo.facilities = [details objectForKey:@"facilities"];
        //        cinemainfo.restaurant = [details objectForKey:@"restaurant"];
        //        cinemainfo.entplace = [details objectForKey:@"entplace"];
        //        
        //        
        //        [[DataStore SharedDataStore].cinema_info_array addObject:cinemainfo];
    }
    
    
    
}
@end

