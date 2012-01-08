//
//  WeatherSummaryController.m
//  wirelessDemo
//
//  Created by Nick Xiao on 1/2/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "WeatherSummaryController.h"
#import "WeatherViewController.h"
#import "WeatherDataMgr.h"


@implementation WeatherSummaryController
@synthesize weathers = myWeathers, scrollView = myScrollView, pageControl = myPageControl;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.weathers = [NSMutableArray array];
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
    
    WeatherDataMgr* wdmgr = [WeatherDataMgr shardWeatherDataMgr];
    [wdmgr addCity:@"101190401"];
    [wdmgr addCity:@"101110101"];
    [wdmgr retrieveData];
    
    self.navigationController.title = @"天气预报";
    
    self.scrollView.delegate = self;
    
//    NSArray *colors = [NSArray arrayWithObjects:[UIColor redColor], [UIColor greenColor], [UIColor blueColor], nil];
//    for (int i = 0; i < colors.count; i++) {
//        CGRect frame;
//        frame.origin.x = self.scrollView.frame.size.width * i;
//        frame.origin.y = 0;
//        frame.size = self.scrollView.frame.size;
//        
//        CGRect frame2 = {0, 0, 0, 0};
//        
//        UIView *subview = [[UIView alloc] initWithFrame:frame2];
//                           subview.frame = frame;
//        subview.backgroundColor = [colors objectAtIndex:i];
//        [self.scrollView addSubview:subview];
//        [subview release];
//    }
//    
//    self.scrollView.contentSize = CGSizeMake(self.scrollView.frame.size.width * colors.count, self.scrollView.frame.size.height);
    
    NSString* cities[] = {@"Suzhou", @"Shanghai", @"Beijing"};
    
    int i = 0;
    for (; i < 3; i ++) {
        CGRect frame;
        frame.origin.x = self.scrollView.frame.size.width * i;
        frame.origin.y = 0;
        frame.size = self.scrollView.frame.size;
        
        WeatherViewController* weather = [[[WeatherViewController alloc] initWithNibName: nil bundle: nil] autorelease];
        [self.weathers addObject: weather];
        UIView *subview = [weather view];
        weather.city.text = cities[i];
        subview.frame = frame;
        [self.scrollView addSubview:subview];
    }
    
    self.scrollView.contentSize = CGSizeMake(self.scrollView.frame.size.width * i, self.scrollView.frame.size.height);
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

- (void)scrollViewDidScroll:(UIScrollView *)sender {
    // Update the page when more than 50% of the previous/next page is visible
    CGFloat pageWidth = self.scrollView.frame.size.width;
    int page = floor((self.scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
    self.pageControl.currentPage = page;
}

@end
