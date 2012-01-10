//
//  MovieInfoController.m
//  wirelessDemo
//
//  Created by Max Qian on 1/9/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "MovieInfoController.h"


@implementation MovieInfoController
@synthesize descp = _descp;
@synthesize comments = _comments;

@synthesize moviepic = _moviepic;
@synthesize moviename = _moviename;
@synthesize moviescore = _moviescore;
@synthesize director = _director;
@synthesize performers = _performers;
@synthesize duration = _duration;

@synthesize btn = _btn;

@synthesize movieinfo = _movieinfo;

@synthesize play = _play;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(id) initWithInfo:(MovieInfo *)p
{
    self = [super initWithNibName:nil bundle:nil];
    if(self){
        _movieinfo = p;
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
    [_moviepic setImage:_movieinfo.tempBitmap];
    
    
    [_moviename setText:[NSString stringWithFormat:@"名称 : %@", _movieinfo.name]];
    [_moviescore setText:[NSString stringWithFormat:@"评分 : %d", [_movieinfo.score integerValue]]];
    [_director setText:[NSString stringWithFormat:@"导演 : %@", _movieinfo.director]];
    [_performers setText:[NSString stringWithFormat:@"主演 : %@", _movieinfo.performers]];    
    [_duration setText:[NSString stringWithFormat:@"时长 : %d分钟", [_movieinfo.duration integerValue]]]; 
    [_descp setText:_movieinfo.description];
    [_descp setEditable:NO];
    [_comments setText:_movieinfo.comments];
    [_comments setEditable:NO];
    
    
    //[_btn addTarget:self action:@selector(showprevue:)forControlEvents:UIControlEventTouchUpInside];
}

- (void)viewDidUnload
{
    [self setMoviepic:nil];
    [self setMoviename:nil];
    [self setMoviescore:nil];
    [self setDirector:nil];
    [self setPerformers:nil];
    [self setDuration:nil];
    [self setDescp:nil];
    [self setComments:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


- (void)dealloc {
    [_moviepic release];
    [_moviename release];
    [_moviescore release];
    [_director release];
    [_performers release];
    [_duration release];
    [_descp release];
    [_comments release];
    [super dealloc];
}

-(IBAction)showprevue:(id)sender
{
//    if(_movieinfo.sample_video_url == nil)
//    {
//        NSString * url = [NSString stringWithFormat:@"http://res.88bx.com/WirelessSZ/movies/videos/%d.mp4",[ _movieinfo.id integerValue]];
//
//        
//        MPMoviePlayerViewController *pc = [[[MPMoviePlayerViewController alloc]initWithContentURL: [NSURL URLWithString: url ]] autorelease];
//        
//        self.play = pc;
//        
//        [self.view addSubview:self.play.view];
//        self.play.view.backgroundColor = [UIColor blackColor];
//        [self presentMoviePlayerViewControllerAnimated:self.play];
//        
//        //set config and start playing.
//        self.play.moviePlayer.movieSourceType = MPMovieSourceTypeFile;
//        self.play.moviePlayer.scalingMode = MPMovieScalingModeAspectFill;
//        [self.play.moviePlayer play];
//    }
}
@end
