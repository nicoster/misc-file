//
//  WeatherViewController.m
//  wirelessDemo
//
//  Created by Nick Xiao on 1/2/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "WeatherViewController.h"
#import "WeatherDetailsController.h"

@implementation WeatherViewController

@synthesize weatherDetailsController = myWeatherDetailsController;
@synthesize city = myCity, currentTemp = myCurrentTemp, weatherIcon = myWeatherIcon;
@synthesize cityID = myCityID;

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

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    int current = arc4random() % 20;
    self.currentTemp.text = [NSString stringWithFormat: @"%d", current];
   
    self.weatherDetailsController = [[WeatherDetailsController alloc] initWithNibName: nil bundle: nil];
    [self.view addSubview:self.weatherDetailsController.view];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    self.weatherDetailsController = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
