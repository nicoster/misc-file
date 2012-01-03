//
//  LauncherViewController.m
//  TTLauncherViewTutorial
//
//  Created by Cezar Signori on 10/18/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "LauncherViewController.h"

@interface LauncherViewController(Private)
- (TTLauncherItem *)launcherItemWithTitle:(NSString *)pTitle image:(NSString *)image URL:(NSString *)url;
@end

@implementation LauncherViewController


- (void)loadView {
	[super loadView];
	
	launcherView = [[TTLauncherView alloc] initWithFrame:self.view.bounds];
	launcherView.backgroundColor = [UIColor whiteColor];
	launcherView.columnCount = 3;
	launcherView.pages = [NSArray arrayWithObjects:
						   [NSArray arrayWithObjects:
							[self launcherItemWithTitle:@"天气" image:@"bundle://weather.png" URL:@"tt://nib/WeatherSummaryController"],
							[self launcherItemWithTitle:@"影讯" image:@"bundle://movies.png" URL:@"tt://nib/MovieSummaryController"]
							, nil]
						  , nil];
	launcherView.delegate = self;
	
	[self.view addSubview:launcherView];
}

- (void)viewDidLoad {
	[super viewDidLoad];
	
	self.title = @"无线苏州";
	
//	UIBarButtonItem *editButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemEdit target:launcherView action:@selector(beginEditing)];
//	self.navigationItem.rightBarButtonItem = editButton;
//	[editButton release];
}

- (void)viewDidUnload {
	[launcherView release];
	launcherView = nil;
	
	[super viewDidUnload];
}


#pragma mark -
#pragma mark Private methods
							
- (TTLauncherItem *)launcherItemWithTitle:(NSString *)pTitle image:(NSString *)image URL:(NSString *)url {
	TTLauncherItem *launcherItem = [[TTLauncherItem alloc] initWithTitle:pTitle 
																   image:image 
																	 URL:url canDelete:YES];

	return [launcherItem autorelease];
}


#pragma mark -
#pragma mark TTLauncherViewDelegate methods

- (void)launcherViewDidBeginEditing:(TTLauncherView*)launcher {
	UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:launcherView action:@selector(endEditing)];
	self.navigationItem.rightBarButtonItem = doneButton;
	[doneButton release];
}

- (void)launcherViewDidEndEditing:(TTLauncherView*)launcher {
	UIBarButtonItem *editButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemEdit target:launcherView action:@selector(endEditing)];
	self.navigationItem.rightBarButtonItem = editButton;
	[editButton release];
}

- (void)launcherView:(TTLauncherView*)launcher didSelectItem:(TTLauncherItem*)item {
	[[TTNavigator navigator] openURLAction:[[TTURLAction actionWithURLPath:item.URL] applyAnimated:YES]];
}


#pragma mark -
#pragma mark Memory Handling methods

- (void)dealloc {
	[launcherView release];
	
	[super dealloc];
}

@end
