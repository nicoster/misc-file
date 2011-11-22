//
//  LauncherViewController.h
//  TTLauncherViewTutorial
//
//  Created by Cezar Signori on 10/18/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Three20/Three20.h>

@interface LauncherViewController : TTViewController<TTLauncherViewDelegate> {
	TTLauncherView *launcherView;
}

@end
