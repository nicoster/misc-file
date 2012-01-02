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
#import "MovieInfo.h"


static        NSString* kRequestURLPath  = @"http://res.88bx.com:8080/wirelesssz/RXService?token=4e799458ecc65cca11ff88bd2ecedca3&cmd=13&city=320500";



@implementation MovieSummaryController

@synthesize flow = _flow;

@synthesize movie_title = _movie_title;
@synthesize movie_director = _movie_director;
@synthesize movie_performers = _movie_performers;
@synthesize movie_category = _movie_category;
@synthesize movie_duration = _movie_duration;
@synthesize movie_startDate = _movie_startDate;


@synthesize movie_info_array          = _movie_info_array;
@synthesize currentIdx = _currentIdx;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        _movie_info_array = [[NSMutableArray array] retain];
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
    // Do any additional setup after loading the view from its nib.
    
    TTURLRequest* request = [TTURLRequest requestWithURL: kRequestURLPath
                            delegate: [[[MovieInfoDelegate alloc] initWithController:self] autorelease]];
    
    request.response = [[[TTURLJSONResponse alloc] init] autorelease];
    
//    NSString * pTest = [self md5:@"WANGYAN-FREY-1974071413"];
//    
//    if([pTest compare:@"4e799458ecc65cca11ff88bd2ecedca3"] == NSOrderedSame)
//    {
//        int a = 0;
//    }
    
    [request send];
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
    [_flow draw];
    
    int nIdx = self.currentIdx;
    //[MovieInfoStore sharedMovieInfoStore].CurrentIdx;
    
    
    MovieInfo *pInfo = [self.movie_info_array objectAtIndex:nIdx];
    
    if(pInfo)
    {
        [_movie_title setText:[NSString stringWithFormat:@"名称 : %@    %d分", pInfo.name, [pInfo.score integerValue]]];
        [_movie_director setText:[NSString stringWithFormat:@"导演 : %@", pInfo.director]];
        [_movie_performers setText:[NSString stringWithFormat:@"主演 : %@", pInfo.performers]];
        [_movie_category setText:[NSString stringWithFormat:@"类型 : %@", pInfo.category]];
        [_movie_duration setText:[NSString stringWithFormat:@"时长 : %d分钟", [pInfo.duration integerValue]]]; 
        
        [_movie_startDate setText:[NSString stringWithFormat:@"上映时间 : %@",pInfo.startDate]];        
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
    return [self.movie_info_array count];
}

- (UIImage *)flowCover:(FlowCoverView *)view cover:(int)image
{
    return [UIImage imageNamed:@"default_movie_post.png"];
	switch (image % 6) {
		case 0:
		default:
			return [UIImage imageNamed:@"cover_1.jpg"];
		case 1:
			return [UIImage imageNamed:@"cover_2.jpg"];
		case 2:
			return [UIImage imageNamed:@"cover_3.jpg"];
		case 3:
			return [UIImage imageNamed:@"cover_4.jpg"];
		case 4:
			return [UIImage imageNamed:@"cover_5.jpg"];
		case 5:
			return [UIImage imageNamed:@"cover_6.jpg"];
	}
}

- (void)flowCover:(FlowCoverView *)view didSelect:(int)image
{
	NSLog(@"Selected Index %d",image);
}

- (void)coverAtIndexWasBroughtToFront:(int )nIndex;
{
    NSLog(@"The front index %d", nIndex);

    self.currentIdx = nIndex;
    
    [self UpdateUI];
}

@end


@implementation MovieInfoDelegate




- (id)initWithController:(id*)controller {
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
    TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
    
    NSArray *entries = JsonResponse.rootObject;
    NSLog(@"%d", [entries count]);

    
    for (NSDictionary* entry in entries) {
        NSDictionary *details = [entry objectForKey:@"MovieInfo"];
        //NSLog(@"entry:%@",entry);
        
            MovieInfo * movieinfo = [[[MovieInfo alloc] init]autorelease];
            movieinfo.name = [details objectForKey:@"movieName"];
            movieinfo.name_en = [details objectForKey:@"movieNameEn"];
            movieinfo.director = [details objectForKey:@"director"];
            movieinfo.performers = [details objectForKey:@"performers"];
            movieinfo.category = [details objectForKey:@"category"];
            movieinfo.description = [details objectForKey:@"description"];
                                  
            movieinfo.duration =[NSNumber numberWithInt:[[details objectForKey:@"duration"] integerValue]];
            movieinfo.status =[NSNumber numberWithInt:[[details objectForKey:@"status"] integerValue]];
            movieinfo.score =[NSNumber numberWithInt:[[details objectForKey:@"score"] integerValue]];
            NSLog(@"score:%d", [movieinfo.score integerValue]);
            
            movieinfo.server_image_url = [details objectForKey:@"imageUrl"];
            movieinfo.comments = [details objectForKey:@"comment"];
            
            movieinfo.startDate = [details objectForKey:@"startDate"];
            
            NSMutableDictionary* hasSchedule = [details objectForKey:@"hasSchedule"];
            if(hasSchedule)
            {
                movieinfo.hasSchedule = hasSchedule;
            }
            
            [_controller.movie_info_array addObject:movieinfo];
            
    }
    
    _controller.currentIdx = 0;
    
    // update UI
    [_controller UpdateUI];
    // get img
    
}

@end