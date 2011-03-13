    //
//  playlistviewcontainer.m
//  i1G
//
//  Created by Nick Xiao on 3/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NavigationSubviewController.h"


@implementation NavigationSubviewController

// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (motion == UIEventSubtypeMotionShake)
    {
        NSLog(@"Shaking..");
        [[NSNotificationCenter defaultCenter] postNotificationName:@"kPlayNext" object:nil];
//		[playlistController playNext];
    }
}

-(BOOL)canBecomeFirstResponder {
    return YES;
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
	UIApplication *application = [UIApplication sharedApplication];
	if([application respondsToSelector:@selector(beginReceivingRemoteControlEvents)])
		[application beginReceivingRemoteControlEvents];
    [self becomeFirstResponder];
}

- (void)viewWillDisappear:(BOOL)animated {
    [self resignFirstResponder];
    [super viewWillDisappear:animated];
}

#pragma mark Remote Control Events
/* The iPod controls will send these events when the app is in the background */
- (void)remoteControlReceivedWithEvent:(UIEvent *)event {
	switch (event.subtype) {
		case UIEventSubtypeRemoteControlNextTrack:
		case UIEventSubtypeMotionShake:
            [[NSNotificationCenter defaultCenter] postNotificationName:@"kPlayNext" object:nil];
			break;
		case UIEventSubtypeRemoteControlPlay:
            [[NSNotificationCenter defaultCenter] postNotificationName:@"kStartPlayer" object:nil];
			break;
		case UIEventSubtypeRemoteControlTogglePlayPause:
		case UIEventSubtypeRemoteControlPause:
            [[NSNotificationCenter defaultCenter] postNotificationName:@"kPausePlayer" object:nil];
			break;
		case UIEventSubtypeRemoteControlStop:
            [[NSNotificationCenter defaultCenter] postNotificationName:@"kStopPlayer" object:nil];
			break;
		default:
			break;
	}
}

@end
