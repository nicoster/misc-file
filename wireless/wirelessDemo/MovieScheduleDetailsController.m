//
//  MovieScheduleDetailsController.m
//  wirelessDemo
//
//  Created by Max Qian on 1/8/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "MovieScheduleDetailsController.h"
#import <extThree20JSON/extThree20JSON.h>

@implementation MovieScheduleDetailsController

@synthesize moviescheduletable = _moviescheduletable;
@synthesize datesegmented = _datesegmented;
@synthesize movieschedule_array = _movieschedule_array;

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

- (id)initwithObj:(NSString*)nibNameOrNil info:(MovieInCinema *)p
{
    
    self = [super initWithNibName:nibNameOrNil bundle:nil];
    if (self) {
        _movieschedule = p;
        
        _movieschedule_array = [[NSMutableArray array]retain];
        
        //NSLog(@"%@", [_movieschedule.moviescheduledetails_array ]);
        
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
    if(_movieschedule != nil)
    {
        [self sendRequest:0 movieid:[_movieschedule.movieid intValue]];        
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
    
    if(_movieschedule)
    {
        [self.datesegmented setSelectedSegmentIndex:_movieschedule.day];
    }
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)segmentControlAction:(id)sender
{
    NSInteger segment = _datesegmented.selectedSegmentIndex; 
    
    NSString* url = [NSString stringWithFormat: moviescheduleRequestURLPath, segment,[_movieschedule.movieid intValue]];
    NSLog(@"url:%@", url);
    
    
    TTURLRequest* request = [TTURLRequest requestWithURL:url delegate:self];
    
    
    request.cachePolicy = TTURLRequestCachePolicyNoCache;
    
    request.response = [[[TTURLJSONResponse alloc] init] autorelease];
    
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
    return [_movieschedule_array count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier] autorelease];
    }
    
    
    UIFont *myFont = [ UIFont fontWithName: @"Arial" size: 17.0 ];
    cell.textLabel.font  = myFont;
    
    ScheduleInfo * scheduleinfo = [_movieschedule_array objectAtIndex:indexPath.row];
    
    NSDate *now = scheduleinfo.movietime;
    NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init]autorelease]; 
    
    
    [dateFormatter setDateFormat:@"HH:mm"];
    //[dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    
    NSString *destDateString = [dateFormatter stringFromDate:now];
    
    /*
     <string-array name="sz_cinema_screen">
     <item>普通</item>
     <item>3D</item>
     <item>IMAX</item>
     <item>IMAX-3D</item>
     <item>数字</item>
     <item>数字-3D</item>
     <item>VIP</item>
     </string-array>
     */
    
    NSArray *array = [[NSArray alloc]initWithObjects:@"普通",@"3D",@"IMax",@"Imax-3D",@"数字",@"数字－3D",@"VIP",nil];
    int screenid = [scheduleinfo.screenid intValue] - 20;
    NSString * temp = [array objectAtIndex:screenid];
    
    NSString * text = [NSString stringWithFormat:@"%@    %@", destDateString,temp];
    
    cell.textLabel.text = text;
                       
    NSString * details;
    if([scheduleinfo.dub isEqualToString:@"en"] )
    {
        details = @"英文版";
    }
    else if([scheduleinfo.dub isEqualToString:@"cn"])
    {
        details = @"中文版";
    }
    
    UIFont *myFont1 = [ UIFont fontWithName: @"Arial" size: 14.0 ];
    cell.detailTextLabel.font  = myFont1;
    cell.detailTextLabel.text = details;
    
    //cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    // Configure the cell...
    
    return cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
//    TTURLAction *urlAction = [[[TTURLAction alloc] initWithURLPath:@"tt://moviedetail/MovieScheduleDetailsController"] autorelease];
//    
//    MovieInCinema *pCinema = [self.cinematable_array objectAtIndex:indexPath.row];
//    urlAction.query = [NSDictionary dictionaryWithObject:pCinema forKey:@"moviedetail"];
//    urlAction.animated = YES;
//    [[TTNavigator navigator] openURLAction:urlAction];
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
    
    int day = self.datesegmented.selectedSegmentIndex;
    
    
    TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
    
    [self.movieschedule_array removeAllObjects];
    
    NSArray *entries = JsonResponse.rootObject;
    
    
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
        
        if([scheduleinfo.cinemaid intValue] == [_movieschedule.cinemaid intValue])
        {
            [_movieschedule_array addObject:scheduleinfo];
        }
    }
    
    
    [self.moviescheduletable reloadData];
}


@end
