//
//  PreferenceViewController.m
//
//  Created by Nick Xiao on 2/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PreferenceViewController.h"

@implementation PreferenceViewController
@synthesize settings, login, viewLogin, viewSettings;

- (void)viewDidLoad {
    [super viewDidLoad];
	self.view.backgroundColor = [UIColor viewFlipsideBackgroundColor];
  
	// LLAMASETTINGS 3:  Make the connections to and from it
	settings = [[LlamaSettings alloc] initWithPlist:@"PreferenceSettings.plist"];
	[settings setDelegate:self];
	[viewSettings setDataSource:settings];
	[viewSettings setDelegate:settings];
//	viewSettings.hidden = YES;
	
	login = [[LlamaSettings alloc] initWithPlist:@"PreferenceLogin.plist"];
	[login setDelegate:self];
	[viewLogin setDataSource:login];
	[viewLogin setDelegate:login];
//	viewLogin.hidden = YES;
}

- (void) settingsChanged:(LlamaSettings *)ls
{
}

- (void) buttonPressed:(NSString *)buttonKey inSettings:(LlamaSettings *)ls
{
	
	CGContextRef context = UIGraphicsGetCurrentContext();
	[UIView beginAnimations:nil context:context];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
	[UIView setAnimationDuration:1.0];
	
	[UIView setAnimationTransition: UIViewAnimationTransitionFlipFromLeft forView:self.view cache:YES];
	NSInteger indexLogin = [[self.view subviews] indexOfObject: self.viewLogin];
	NSInteger indexSettings = [[self.view subviews] indexOfObject: self.viewSettings];
	//	NSInteger purple = [[whiteBackdrop subviews] indexOfObject:[whiteBackdrop viewWithTag:999]];
	//	NSInteger maroon = [[whiteBackdrop subviews] indexOfObject:[whiteBackdrop viewWithTag:998]];
	[self.view exchangeSubviewAtIndex:indexLogin withSubviewAtIndex:indexSettings];
	//	
	//	[UIView setAnimationDelegate:self];
	[UIView setAnimationDidStopSelector:@selector(animationFinished:)];
	[UIView commitAnimations];	
	 	
}

- (void) dealloc
{
	settings = nil;
	[super dealloc];
}

@end
