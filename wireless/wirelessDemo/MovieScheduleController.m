//
//  MovieScheduleController.m
//  wirelessDemo
//
//  Created by Max Qian on 1/6/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "MovieScheduleController.h"
#import <extThree20JSON/extThree20JSON.h>



@implementation MovieInCinema

@synthesize movieid = _movieid;
@synthesize cinemaid = _cinemaid;
@synthesize movieCount = _movieCount;
@synthesize day = _day;
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

-(void)sendRequest: (NSInteger)day movieid:(NSInteger )id
{
    NSString* url = [NSString stringWithFormat: moviescheduleRequestURLPath, day,id];
    
    TTURLRequest* request = [TTURLRequest requestWithURL:url delegate:self];
    
    request.cachePolicy = TTURLRequestCachePolicyNoCache;
    
    request.response = [[[TTURLJSONResponse alloc] init] autorelease];
    
    [request send];
    
    for(int i= 0; i< self.datesegmented.numberOfSegments; i++)
    {
        if(day == i)
            [self.datesegmented setEnabled:YES forSegmentAtIndex:i];
        else
            [self.datesegmented setEnabled:NO forSegmentAtIndex:i];
    }
}

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
    
    if(_movieinfo.movieSchedule == nil)
    {
        [self sendRequest:0 movieid:[_movieinfo.id intValue]];        
    }

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
    
    
    [_cinematable_array removeAllObjects];
    
    [self sendRequest:segment movieid:[_movieinfo.id intValue]];
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
    TTURLAction *urlAction = [[[TTURLAction alloc] initWithURLPath:@"tt://moviedetail/MovieScheduleDetailsController"] autorelease];
    
    MovieInCinema *pCinema = [self.cinematable_array objectAtIndex:indexPath.row];
    urlAction.query = [NSDictionary dictionaryWithObject:pCinema forKey:@"moviedetail"];
    urlAction.animated = YES;
    [[TTNavigator navigator] openURLAction:urlAction];
}

////////////////////////////////////
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
    
    for(int i= 0; i< self.datesegmented.numberOfSegments; i++)
    {
        [self.datesegmented setEnabled:YES forSegmentAtIndex:i];
    }
    
    
    TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
    
    int day = [[request.parameters objectForKey:@"movieDay"] intValue];
    
    NSLog(@"parameters key: %@ -- values: %@", [request.parameters allKeys],[request.parameters allValues]);
    
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
        pCinema.day = day;
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




