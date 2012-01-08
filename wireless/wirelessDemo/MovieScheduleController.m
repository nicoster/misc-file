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

@implementation MovieInCinema

@synthesize movieid = _movieid;
@synthesize cinemaid = _cinemaid;
@synthesize movieCount = _movieCount;
@synthesize moviescheduledetails_array = _moviescheduledetails_array;

-(id)init
{
    if(self)
    {
        _movieCount = 0;
        _moviescheduledetails_array = [[NSMutableArray array]retain];
    }
    return self;
}

@end

@implementation MovieScheduleController
@synthesize movieinfo = _movieinfo;
@synthesize cinematable = _cinematable;
@synthesize datesegmented = _datesegmented;
@synthesize cinematable_array = _cinematable_array;

- (id)initwithObj:(NSString*)nibNameOrNil info:(MovieInfo *)p
{
    
    self = [super initWithNibName:nibNameOrNil bundle:nil];
    if (self) {
        _movieinfo = p;
        
        if(self.cinematable_array == nil)
        {
            self.cinematable_array = [[NSMutableArray array]retain];
        }
        else
        {
            [self.cinematable_array removeAllObjects];
        }
        if(_movieinfo.movieSchedule == nil)
        {
            NSString* url = [NSString stringWithFormat: moviescheduleRequestURLPath, 0,[_movieinfo.id intValue]];
            NSLog(@"url:%@", url);
           
            
            TTURLRequest* request = [TTURLRequest requestWithURL:url delegate:self];
            
            
            request.cachePolicy = TTURLRequestCachePolicyNoCache;
            
            request.response = [[[TTURLJSONResponse alloc] init] autorelease];
            
            [request send];

        }
        _cinematable.delegate = self;
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

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.

//    NSDate *now = [NSDate date];
//    NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init]autorelease]; 
//    
//    
//    [dateFormatter setDateFormat:@"MM月dd日"];
//    //[dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
//    
//    NSString *destDateString = [dateFormatter stringFromDate:now];
//    NSLog(@"date:%@",destDateString);
//    
//    [self.datesegmented setTitle:destDateString forSegmentAtIndex:0];

}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}
-(void) viewWillAppear:(BOOL)animated
{
    NSDate *now = [NSDate date];
    NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init]autorelease]; 
    
    
    [dateFormatter setDateFormat:@"MM月dd日"];
    //[dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    
    NSString *destDateString = [dateFormatter stringFromDate:now];
    NSLog(@"date:%@",destDateString);
    
    NSTimeInterval secondsIn24Hours = 24 * 60 * 60;
    NSTimeInterval secondsIn48Hours = 48 *60 * 60;
    NSDate *date24HoursAhead = [now dateByAddingTimeInterval:secondsIn24Hours];
    NSDate *date48HoursAhead = [now dateByAddingTimeInterval:secondsIn48Hours];
    
    
    
    
    [self.datesegmented setTitle:destDateString forSegmentAtIndex:0];
    
    destDateString = [dateFormatter stringFromDate:date24HoursAhead];
    [self.datesegmented setTitle:destDateString forSegmentAtIndex:1];
    
    destDateString = [dateFormatter stringFromDate:date48HoursAhead];
    [self.datesegmented setTitle:destDateString forSegmentAtIndex:2];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)segmentControlAction:(id)sender
{
    NSInteger segment = _datesegmented.selectedSegmentIndex; 
    
    NSString* url = [NSString stringWithFormat: moviescheduleRequestURLPath, segment,[_movieinfo.id intValue]];
    NSLog(@"url:%@", url);
    
    
    TTURLRequest* request = [TTURLRequest requestWithURL:url delegate:self];
    
    
    request.cachePolicy = TTURLRequestCachePolicyNoCache;
    
    request.response = [[[TTURLJSONResponse alloc] init] autorelease];
    
    [_cinematable_array removeAllObjects];
    
    [request send];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [self.cinematable_array count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier] autorelease];
    }
    
    NSString * name;
    //for (CinemaInfo* ci in [DataStore SharedDataStore].cinema_info_array) 
    for(int i = 0; i< [[DataStore SharedDataStore].cinema_info_array count];i++)
    {
        CinemaInfo * ci = [[DataStore SharedDataStore].cinema_info_array objectAtIndex:i];
        
        if([ci.cinemaid intValue] == [((MovieInCinema*)[self.cinematable_array objectAtIndex:indexPath.row]).cinemaid intValue])
        {
            name = ci.cinemaname;
            break;
        }
    }
    
    UIFont *myFont = [ UIFont fontWithName: @"Arial" size: 17.0 ];
    cell.textLabel.font  = myFont;

    cell.textLabel.text = name;
    NSString * details = [NSString stringWithFormat:@"剩余场次 : %d",((MovieInCinema*)[self.cinematable_array objectAtIndex:indexPath.row]).movieCount];
    
    UIFont *myFont1 = [ UIFont fontWithName: @"Arial" size: 14.0 ];
    cell.detailTextLabel.font  = myFont1;
    cell.detailTextLabel.text = details;
    
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


#pragma mark -
#pragma mark TTURLRequestDelegate
- (void)requestDidStartLoad:(TTURLRequest*)request {
    //    [_requestButton setTitle:@"Loading..." forState:UIControlStateNormal];
    
}

- (void)request:(TTURLRequest*)request didFailLoadWithError:(NSError*)error {
    
}


///////////////////////////////////////////////////////////////////////////////////////////////////
- (void)requestDidFinishLoad:(TTURLRequest*)request 
{
    TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
    
    int day = [[request.parameters objectForKey:@"movieDay"] intValue];
    
    [self.movieinfo.movieSchedule removeAllObjects];
    
    NSArray *entries = JsonResponse.rootObject;
    
    NSMutableDictionary * _ci_dictionary = [NSMutableDictionary dictionary];
    
    
    for (NSDictionary* entry in entries) {
        NSDictionary *details = [entry objectForKey:@"Schedule"];
        
        ScheduleInfo * scheduleinfo = [[[ScheduleInfo alloc] init] autorelease];
        
        scheduleinfo.movieid = [details objectForKey:@"movieid"];
        scheduleinfo.cinemaid = [details objectForKey:@"cinemaid"];
        scheduleinfo.screenid = [details objectForKey:@"screen"];
        scheduleinfo.price = [details objectForKey:@"price"];
        
        
        // convert time
        NSString * p =[details objectForKey:@"time"];
        NSDateFormatter* format=[[NSDateFormatter new]autorelease];
        [format setTimeZone:[NSTimeZone timeZoneWithName:@"GMT"]];
        [format setDateFormat:(@"yyyy/MM/dd HH:mm")]; // HH:mm:ss
        scheduleinfo.movietime = [format dateFromString:p];
        NSLog(@"time:%@",scheduleinfo.movietime);
        // end
        
        int n = (int)[NSNumber numberWithInt:[[details objectForKey:@"language"] intValue]] ;
        scheduleinfo.dub  = (n == 0?@"en":@"cn");
        
        
        [[self.movieinfo.movieSchedule objectAtIndex:day] addObject:scheduleinfo];
        
        
        
        MovieInCinema *pCinema;
        
        if([_ci_dictionary objectForKey:scheduleinfo.cinemaid] == nil)
        {
            
            pCinema = [[[MovieInCinema alloc]init]autorelease];
        }
        else
        {
            pCinema = [_ci_dictionary objectForKey:scheduleinfo.cinemaid];
        }
        
        pCinema.movieid = scheduleinfo.movieid;
        pCinema.cinemaid = scheduleinfo.cinemaid;
        [pCinema.moviescheduledetails_array addObject:scheduleinfo];
        
        NSDate *now = [NSDate date];
        //        NSTimeZone *zone = [NSTimeZone systemTimeZone];
        //        NSInteger interval = [zone secondsFromGMTForDate: date];
        //        NSDate *now = [date  dateByAddingTimeInterval: interval];
        
        
        
        if([now compare:scheduleinfo.movietime] == NSOrderedAscending)
        {
            pCinema.movieCount++;
        }
        
        [_ci_dictionary setObject:pCinema forKey:pCinema.cinemaid];
    }
    
    for (id key in _ci_dictionary)
    {
        [self.cinematable_array addObject: [_ci_dictionary objectForKey:key]];
    }
    
    [self.cinematable reloadData];
}

@end





