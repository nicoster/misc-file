//
//  PreferenceViewController.m
//
//  Created by Nick Xiao on 2/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PreferenceViewController.h"
#import "NX1GClient.h"
#import "i1GAppDelegate.h"
#import "PlaylistViewController.h"



@implementation PreferenceViewController
@synthesize settings, login, viewLogin, viewSettings;

- (void) dealloc
{
	self.settings = nil;
	self.login = nil;
	self.viewLogin = nil;
	self.viewSettings = nil;
	[super dealloc];
}

- (void) animationFinished:(NSString *)animationID finished:(BOOL)finished context:(void *)context
{
	[[PlaylistViewController sharedPlaylistViewCtrlr].overlay removeFromSuperview];	
}

- (void)flipViews
{
	[PlaylistViewController sharedPlaylistViewCtrlr].overlay.alpha = 0.1;
	
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
	[UIView setAnimationDelegate:self];
	[UIView setAnimationDidStopSelector:@selector(animationFinished:finished:context:)];
	[UIView commitAnimations];	
}

- (void)loginDidFinish:(NSNotification *)notification;
{
	hid = 0;
	NSString* ret = [notification object];
	
	if (![ret isEqualToString:@"0000"])
	{
		[[i1GAppDelegate sharedAppDelegate] forView:self.view showPrompt:@"Unable to sign in"];
		return;
	}
	
	[[NSUserDefaults standardUserDefaults] setObject:[NSString stringWithFormat:@"Welcome, %@", [[NSUserDefaults standardUserDefaults] stringForKey:@"kPreferenceUser"]] 
											  forKey:@"title4section0"];
	[self.viewSettings reloadData];
	[self flipViews];
}

- (void)logoutDidFinish:(NSNotification *)notification;
{
	hid = 0;
	NSString* ret = [notification object];
	
	if (![ret isEqualToString:@"0000"])
	{
		[[i1GAppDelegate sharedAppDelegate] forView:self.view showPrompt:@"Unable to sign out"];
//		UIAlertView *alert = [
//							  [[UIAlertView alloc]
//							   initWithTitle:@"1G1G"
//							   message:@"Unable to sign out."
//							   delegate:self
//							   cancelButtonTitle:NSLocalizedString(@"OK", @"")
//							   otherButtonTitles: nil]
//							  autorelease];
//		[alert
//		 performSelector:@selector(show)
//		 onThread:[NSThread mainThread]
//		 withObject:nil
//		 waitUntilDone:NO];
		return;
	}
	
	[[NSUserDefaults standardUserDefaults] setObject:nil
											  forKey:@"title4section0"];
	[self.viewLogin reloadData];
	
	[self flipViews];
}

- (void)songDidLoad:(NSNotification *)notification;
{
	[[NSNotificationCenter defaultCenter] removeObserver:self name:@"kSongDidLoad" object:nil];
	[self buttonPressed:@"kPreferenceSignin" inSettings:self.login];
}

- (void)viewDidLoad {
    [super viewDidLoad];
	hid = 0;

//	self.view.backgroundColor = [UIColor viewFlipsideBackgroundColor];

	// LLAMASETTINGS 3:  Make the connections to and from it
	self.settings = [[LlamaSettings alloc] initWithPlist:@"PreferenceSettings.plist"];
	[settings setDelegate:self];
	[viewSettings setDataSource:settings];
	[viewSettings setDelegate:settings];
	
	self.login = [[LlamaSettings alloc] initWithPlist:@"PreferenceLogin.plist"];
	[login setDelegate:self];
	[viewLogin setDataSource:login];
	[viewLogin setDelegate:login];
	
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(songDidLoad:) name:@"kSongDidLoad" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginDidFinish:) name:@"kLoginDidFinish" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(logoutDidFinish:) name:@"kLogoutDidFinish" object:nil];

}

- (void) settingsChanged:(LlamaSettings *)ls
{
}

- (void) buttonPressed:(NSString *)buttonKey inSettings:(LlamaSettings *)ls
{
	if (hid) {
		return;
	}
	if ([buttonKey isEqualToString:@"kPreferenceSignin"]) {
		UIView* textfield = [self.viewLogin viewWithTag:1001];
		[textfield resignFirstResponder];
		textfield = [self.viewLogin viewWithTag:1002];
		[textfield resignFirstResponder];
		
		hid = [[NX1GClient shared1GClient] loginWithUser:[[NSUserDefaults standardUserDefaults] stringForKey:@"kPreferenceUser"] 
									   andPassword:[[NSUserDefaults standardUserDefaults] stringForKey:@"kPreferencePasswd"]];
	}
	else if ([buttonKey isEqualToString:@"kPreferenceSignout"]) {
		hid = [[NX1GClient shared1GClient] logout];
	}
	
	[PlaylistViewController sharedPlaylistViewCtrlr].overlay.alpha = 1;
	[self.view addSubview:[PlaylistViewController sharedPlaylistViewCtrlr].overlay];
}

- (void)viewDidUnload {
	[super viewDidUnload];
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	
}


- (void) showPlaylistView: (id) sender
{
	[[[i1GAppDelegate sharedAppDelegate] captionBar] pushViewController:[[i1GAppDelegate sharedAppDelegate] playlistController] animated:YES];
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
//	self.navigationItem.rightBarButtonItem = BARBUTTON(@"亦歌",@selector (showPlaylistView:));
}

@end
