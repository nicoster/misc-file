//
//  PreferenceViewController.m
//
//  Created by Nick Xiao on 2/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PreferenceViewController.h"

@implementation PreferenceViewController
@synthesize settings;

- (void)viewDidLoad {
    [super viewDidLoad];
    
	// LLAMASETTINGS 3:  Make the connections to and from it
	settings = [[LlamaSettings alloc] initWithPlist:@"mySettings.plist"];
	[settings setDelegate:self];
	[(UITableView*)self.view setDataSource:settings];
	[(UITableView*)self.view setDelegate:settings];
}

- (void) settingsChanged:(LlamaSettings *)ls
{
}

- (void) buttonPressed:(NSString *)buttonKey inSettings:(LlamaSettings *)ls
{
}

- (void) dealloc
{
	settings = nil;
	[super dealloc];
}

@end
