//
//  MovieSummaryController.m
//  wirelessDemo
//
//  Created by Max Qian on 12/22/11.
//  Copyright (c) 2011 Cisco-Webex. All rights reserved.
//

#import "MovieSummaryController.h"
#import <extThree20JSON/extThree20JSON.h>
#import <CommonCrypto/CommonDigest.h>

#import "CinemaInfo.h"


static NSString* movieinfoRequestURLPath  = @"http://res.88bx.com:8080/wirelesssz/RXService?token=4e799458ecc65cca11ff88bd2ecedca3&cmd=13&city=320500";
static NSString* cinemainfoRequestURLPath  = @"http://res.88bx.com:8080/wirelesssz/RXService?token=88755a311e935512a5c0f57fc7119406&cmd=14&city=320500";




@implementation MovieSummaryController

@synthesize flow = _flow;

@synthesize movie_title = _movie_title;
@synthesize movie_director = _movie_director;
@synthesize movie_performers = _movie_performers;
@synthesize movie_category = _movie_category;
@synthesize movie_duration = _movie_duration;
@synthesize movie_startDate = _movie_startDate;


@synthesize currentIdx = _currentIdx;



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

- (NSString *) md5:(NSString *) input
{
    const char *cStr = [input UTF8String];
    unsigned char digest[16];
    CC_MD5( cStr, strlen(cStr), digest ); // This is the md5 call
    
    NSMutableString *output = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    
    for(int i = 0; i < CC_MD5_DIGEST_LENGTH; i++)
        [output appendFormat:@"%02x", digest[i]];
    
    return  output;
    
}

#pragma mark - View lifecycle
- (void)viewWillAppear:(BOOL)animated
{
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title = @"全部影片";
    // Do any additional setup after loading the view from its nib.
    
//  [[TTURLCache sharedCache] removeAll:YES];
    MovieInfoDelegate *movieinfodelegate = [(MovieInfoDelegate*)[MovieInfoDelegate alloc] initWithController:self];
    

    TTURLRequest* request = [TTURLRequest requestWithURL:movieinfoRequestURLPath delegate:movieinfodelegate];
    
    
    request.cachePolicy = TTURLRequestCachePolicyNoCache;
    
    request.response = [[[TTURLJSONResponse alloc] init] autorelease];
    
//    NSString * pTest = [self md5:@"WANGYAN-FREY-1974071413"];
//    
//    if([pTest compare:@"4e799458ecc65cca11ff88bd2ecedca3"] == NSOrderedSame)
//    {
//        int a = 0;
//    }

    BOOL b = [request send];
    NSLog(@"abcde:%d",b);
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

- (void) UpdateUI
{
    
    if([[DataStore SharedDataStore].movie_info_array count] == 0)
    {
        return;
    }
    [_flow draw];
    
    int nIdx = self.currentIdx;
    

    MovieInfo *pInfo = [[DataStore SharedDataStore].movie_info_array objectAtIndex:nIdx];
    
    if(pInfo)
    {
        [_movie_title setText:[NSString stringWithFormat:@"名称 : %@    %d分", pInfo.name, [pInfo.score integerValue]]];
        [_movie_director setText:[NSString stringWithFormat:@"导演 : %@", pInfo.director]];
        [_movie_performers setText:[NSString stringWithFormat:@"主演 : %@", pInfo.performers]];
        [_movie_category setText:[NSString stringWithFormat:@"类型 : %@", pInfo.category]];
        [_movie_duration setText:[NSString stringWithFormat:@"时长 : %d分钟", [pInfo.duration integerValue]]]; 
        
        NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init] autorelease]; 
        
        //zzz表示时区，zzz可以删除，这样返回的日期字符将不包含时区信息 +0000。
        
        [dateFormatter setDateFormat:@"yyyy-MM-dd"];
        
        NSString *destDateString = [dateFormatter stringFromDate:pInfo.startDate];
        
        [_movie_startDate setText:[NSString stringWithFormat:@"上映时间 : %@",destDateString]];        
    }
    
}

- (IBAction)viewCinema
{
    if([DataStore SharedDataStore].movie_info_array != nil && [[DataStore SharedDataStore].movie_info_array count] != 0)
    {
        MovieInfo *p = [[DataStore SharedDataStore].movie_info_array objectAtIndex:_currentIdx];
        if(p)
        {
            
            TTURLAction *urlAction = [[[TTURLAction alloc] initWithURLPath:@"tt://obj/MovieScheduleController"] autorelease];
            urlAction.query = [NSDictionary dictionaryWithObject:p forKey:@"movieinfo"];
            urlAction.animated = YES;
            [[TTNavigator navigator] openURLAction:urlAction];
            
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////



/************************************************************************/
/*																		*/
/*	FlowCover Callbacks													*/
/*																		*/
/************************************************************************/

- (int)flowCoverNumberImages:(FlowCoverView *)view
{
//    if([MovieInfoStore sharedMovieInfoStore].MovieInfo != nil)
//    {
//        return [[MovieInfoStore sharedMovieInfoStore].MovieInfo count];
//    }
    return [[DataStore SharedDataStore].movie_info_array count];
}

- (ImageData *)flowCover:(FlowCoverView *)view cover:(int)image
{
    MovieInfo *pInfo = [[DataStore SharedDataStore].movie_info_array objectAtIndex:image];
    
    ImageData * p = [[ImageData alloc]autorelease];
    
    if( pInfo.tempBitmap != nil)
    {
        p.ImageTexture = pInfo.tempBitmap;
        p.bIsDefault = NO;
        return p;
    }
    
    p.ImageTexture = [UIImage imageNamed:@"default_movie_post.png"];
    p.bIsDefault = YES;
    
    return p;
}

- (void)flowCover:(FlowCoverView *)view didSelect:(int)image
{
    if([DataStore SharedDataStore].movie_info_array != nil && [[DataStore SharedDataStore].movie_info_array count] != 0)
    {
        MovieInfo *p = [[DataStore SharedDataStore].movie_info_array objectAtIndex:image];
        if(p)
        {
            
            TTURLAction *urlAction = [[[TTURLAction alloc] initWithURLPath:@"tt://obj/MovieScheduleController"] autorelease];
            urlAction.query = [NSDictionary dictionaryWithObject:p forKey:@"movieinfo"];
            urlAction.animated = YES;
            [[TTNavigator navigator] openURLAction:urlAction];
            
        }
    }
}

- (void)coverAtIndexWasBroughtToFront:(int )nIndex;
{
    self.currentIdx = nIndex;
    
    [self UpdateUI];
}

@end


@implementation MovieInfoDelegate


- (id)initWithController:(MovieSummaryController *)controller {
    self = [super init];
    if (self) {
        _controller = (MovieSummaryController*)controller;
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
- (void)requestDidFinishLoad:(TTURLRequest*)request {
//    return;
    TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
    
    NSArray *entries = JsonResponse.rootObject;
    NSLog(@"%d", [entries count]);
    
    // get cinema info
    CinemaInfoDelegate *cinemainfodelegate = [(CinemaInfoDelegate *)[CinemaInfoDelegate alloc] initWithController:_controller];
    
    TTURLRequest* requestforcinemainfo = [TTURLRequest requestWithURL:cinemainfoRequestURLPath delegate:cinemainfodelegate];
    
    requestforcinemainfo.cachePolicy = TTURLRequestCachePolicyNoCache;
    
    requestforcinemainfo.response = [[[TTURLJSONResponse alloc] init] autorelease];
    
    [requestforcinemainfo send];
    // end

    ImageDelegate *imgdelegate = [(ImageDelegate*)[ImageDelegate alloc] initWithController:_controller];
    

    
    for (NSDictionary* entry in entries) {
        NSDictionary *details = [entry objectForKey:@"MovieInfo"];
        //NSLog(@"entry: %@",entry);
        
        MovieInfo * movieinfo = [[[MovieInfo alloc] init]autorelease];
        movieinfo.id = [details objectForKey:@"movieId"];
        movieinfo.name = [details objectForKey:@"movieName"];
        //NSLog(@"moviename: %@", movieinfo.name);
        
        
        movieinfo.name_en = [details objectForKey:@"movieNameEn"];
        movieinfo.director = [details objectForKey:@"director"];
        movieinfo.performers = [details objectForKey:@"performers"];
        movieinfo.category = [details objectForKey:@"category"];
        movieinfo.description = [details objectForKey:@"description"];
                                  
        movieinfo.duration =[NSNumber numberWithInt:[[details objectForKey:@"duration"] integerValue]];
        movieinfo.status =[NSNumber numberWithInt:[[details objectForKey:@"status"] integerValue]];
        movieinfo.score =[NSNumber numberWithInt:[[details objectForKey:@"score"] integerValue]];
            
        movieinfo.server_image_url = [details objectForKey:@"imageUrl"];
//        NSLog(@"serverurl: %@",movieinfo.server_image_url);
        
        movieinfo.comments = [details objectForKey:@"comment"];
        
        // convert time
        NSString * p =[details objectForKey:@"startDate"];
        NSDateFormatter* format=[[NSDateFormatter new]autorelease];
        [format setTimeZone:[NSTimeZone timeZoneWithName:@"GMT"]];
        [format setDateFormat:(@"yyyy/MM/dd")];
        movieinfo.startDate = [format dateFromString:p];
        // end
            
        NSMutableDictionary* hasSchedule = [details objectForKey:@"hasSchedule"];
        if(hasSchedule)
        {
            movieinfo.hasSchedule = hasSchedule;
        }
            
        [[DataStore SharedDataStore].movie_info_array addObject:movieinfo];
        
        // Get Image
        TTURLRequest* request = [TTURLRequest requestWithURL:movieinfo.server_image_url delegate:imgdelegate];
        
        request.cachePolicy = TTURLRequestCachePolicyNoCache;
        
        request.response = [[[TTURLImageResponse alloc] init] autorelease];
        
        [request send];
        // end
            
    }
    
    _controller.currentIdx = 0;
    
    // update UI
    [_controller UpdateUI];
    
}
@end


@implementation ImageDelegate

- (id)initWithController:(MovieSummaryController *)controller {
//    [super init];
    if (self) {
        _controller = (MovieSummaryController*)controller;
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
    TTURLImageResponse* imageResponse = (TTURLImageResponse*)request.response;
    NSString * strRequestURL = request.urlPath; 
    
    for (NSUInteger i = 0; i<[[DataStore SharedDataStore].movie_info_array count]; i++) 
    {
        MovieInfo *p = [[DataStore SharedDataStore].movie_info_array objectAtIndex:i];
        
        if([p.server_image_url compare:strRequestURL] == NSOrderedSame)
        {    
            p.tempBitmap = imageResponse.image;
            break;
        }
        else
        {
            //NSLog(@"reqURL:%@  sev_URL:%@  Idx:%d", strRequestURL, p.server_image_url,i);
        }
        
    }
 
    [_controller UpdateUI];
}
@end

@implementation CinemaInfoDelegate

- (id)initWithController:(MovieSummaryController *)controller {
    //    [super init];
    if (self) {
        _controller = (MovieSummaryController*)controller;
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
    //NSLog(@"%d", [entries count]);
    
    for (NSDictionary* entry in entries) {
        NSDictionary *details = [entry objectForKey:@"CinemaInfo"];
        //NSLog(@"entry: %@",details);
        
        CinemaInfo * cinemainfo = [[[CinemaInfo alloc] init]autorelease];
        cinemainfo.cinemaid = [NSNumber numberWithInt:[[details objectForKey:@"cinemaId"] integerValue]];
        
        cinemainfo.cinemaname = [details objectForKey:@"cinemaName"];
        //NSLog(@"cinemaid: %d, name:%@", [cinemainfo.cinemaid intValue], cinemainfo.cinemaname);
        cinemainfo.address = [details objectForKey:@"address"];
        cinemainfo.city = [details objectForKey:@"city"];
        cinemainfo.area = [details objectForKey:@"area"];
        cinemainfo.description = [details objectForKey:@"description"];
        
            
        cinemainfo.imageurl = [details objectForKey:@"imageUrl"];
        cinemainfo.logourl = [details objectForKey:@"logoUrl"];
        cinemainfo.busline = [details objectForKey:@"bus"];
        cinemainfo.telphone = [details objectForKey:@"telphone"];
        cinemainfo.opentime = [details objectForKey:@"opentime"];
        cinemainfo.facilities = [details objectForKey:@"facilities"];
        cinemainfo.restaurant = [details objectForKey:@"restaurant"];
        cinemainfo.entplace = [details objectForKey:@"entplace"];
        
        
        [[DataStore SharedDataStore].cinema_info_array addObject:cinemainfo];
    }
    


}
@end