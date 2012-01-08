//
//  MovieScheduleDetailsController.m
//  wirelessDemo
//
//  Created by Max Qian on 1/8/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "MovieScheduleDetailsController.h"
#import "MovieScheduleController.h"

@implementation MovieScheduleDetailsController

- (id)initwithObj:(NSString*)nibNameOrNil info:(MovieInCinema *)p
{
    
    self = [super initWithNibName:nibNameOrNil bundle:nil];
    if (self) {
        
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

@end
