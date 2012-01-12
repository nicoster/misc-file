//
//  MovieScheduleController.m
//  wirelessDemo
//
//  Created by Max Qian on 1/6/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "MovieScheduleController.h"
#import <extThree20JSON/extThree20JSON.h>
#import "MovieInfoController.h"


@implementation MovieInCinema

@synthesize movieid = _movieid;
@synthesize cinemaid = _cinemaid;
@synthesize movieCount = _movieCount;
@synthesize day = _day;

-(id)init
{
    if(self)
    {
        _movieCount = 0;
    }
    return self;
}

@end

@implementation MovieScheduleController
@synthesize mybutton = _button;
@synthesize movieinfo = _movieinfo;
@synthesize cinematable = _cinematable;
@synthesize datesegmented = _datesegmented;
@synthesize cinematable_array = _cinematable_array;

@synthesize movieinfoController = _movieinfoController;



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
    
    self.title = @"排片";
    
    if(_movieinfo.movieSchedule == nil)
    {
        [self sendRequest:0 movieid:[_movieinfo.id intValue]];        
    }
    
    self.movieinfoController = [[(MovieInfoController*)[MovieInfoController alloc]initWithInfo:_movieinfo] autorelease];

    //_movieinfoview = p.view;
    
    [[self view] addSubview:_movieinfoController.view ];

    
    CGRect theFrame = [_movieinfoController.view frame];
    theFrame.origin.y = -460.0f;
    _movieinfoController.view.frame = theFrame;
    
    [self.view bringSubviewToFront:_button];
    [self.view bringSubviewToFront:self.navigationController.navigationBar];
    

}

- (void)viewDidUnload
{
    [self setMybutton:nil];
    
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

-(void)animationDidStop:(NSString *) url
{
    NSLog(@"%@",url);
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    [UIView beginAnimations:@"Curl" context:context];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
    [UIView setAnimationDuration:0.5];
    CGRect rect1=[_button frame];
    if([url isEqualToString:@"Curl1"])
    {
        [_button setTitle:@"收起" forState:UIControlStateNormal & UIControlStateHighlighted & UIControlStateSelected];
        rect1.origin.y = 416.0f - rect1.size.height;
    }
    else if( [url isEqualToString:@"Curl2"])
    {

        [_button setTitle:@"影片详情" forState:UIControlStateNormal & UIControlStateHighlighted & UIControlStateSelected];
        rect1.origin.y = 0.0f;
    }
    
    [_button setFrame:rect1];
    [UIView commitAnimations];

}


-(IBAction)buttonSwitch:(id)sender
{
	CGContextRef context = UIGraphicsGetCurrentContext();
    if([_movieinfoController.view frame].origin.y< -450.0f)
    {
        [UIView beginAnimations:@"Curl1" context:context];
    }
    else
    {
        [UIView beginAnimations:@"Curl2" context:context];
    }
	[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
	[UIView setAnimationDuration:1.0f];
    [UIView setAnimationDelegate:self];
	CGRect rect = [_movieinfoController.view frame];
	CGRect rect1=[_button frame];
    CGRect rect2 = [self.navigationController.navigationBar frame];
    if(rect.origin.y < -450.0f)
    {
        rect.origin.y = -44.0f;
        rect1.origin.y = 416.0f;
        rect2.origin.y = -24.0f;
        
    }
    else
    {
        rect.origin.y = -460.0f;
        rect1.origin.y = -44.0f;
        rect2.origin.y = 20.0f;
    }
    
    [_button setFrame:rect1];
    [_movieinfoController.view setFrame:rect];
    [self.navigationController.navigationBar setFrame:rect2];
    [UIView commitAnimations];
    
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
    
    int day = self.datesegmented.selectedSegmentIndex;
    
    
    TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
    
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
        
        NSDate *date = [NSDate date];
        NSTimeZone *zone = [NSTimeZone systemTimeZone];
        NSInteger interval = [zone secondsFromGMTForDate: date];
        NSDate *now = [date  dateByAddingTimeInterval: interval];
        
        
        
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

- (void)dealloc {
    [_button release];
    [super dealloc];
}
@end





