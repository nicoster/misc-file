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
    
    self.title = @"天气预报";
    self.scrollView.delegate = self;
    
    NSString* cities[] = {@"101190401", @"101110101"};
    
    WeatherDataMgr* wdmgr = [WeatherDataMgr sharedWeatherDataMgr];
    int i = 0;
    for (; i < sizeof(cities) / sizeof(cities[0]); i ++) {
        CGRect frame;
        frame.origin.x = self.scrollView.frame.size.width * i;
        frame.origin.y = 0;
        frame.size = self.scrollView.frame.size;
        
        WeatherViewController* weather = [[[WeatherViewController alloc] initWithNibName: nil bundle: nil] autorelease];
        weather.cityID = cities[i];
        [self.weathers addObject: weather];
        UIView *subview = [weather view];
        subview.frame = frame;
        [self.scrollView addSubview:subview];

        [wdmgr addCity:cities[i]];
    }
    
    [wdmgr retrieveData];
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
