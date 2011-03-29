//
//  PreferenceViewController.h
//
//  Created by Nick Xiao on 2/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "LlamaSettings.h"

enum LoginState {
	SIGNED_OFF = 0,
	SIGNED_IN = 1,
};

@interface PreferenceViewController : UIViewController <LlamaSettingsDelegate> {
	LlamaSettings *settings, *login;
    UIViewController* container;
	int hid;
	int loginstate;
}
@property (nonatomic, retain) LlamaSettings *settings, *login;
@property (nonatomic, retain) IBOutlet UITableView *viewLogin, *viewSettings;
@property (nonatomic, retain) UIViewController* container;
@property (nonatomic, assign) int loginstate;
@end
