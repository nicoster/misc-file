//
//  MovieScheduleController.h
//  wirelessDemo
//
//  Created by Max Qian on 1/6/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "MovieInfo.h"
#import <Three20/Three20.h>

@interface MovieScheduleController : UIViewController<UITableViewDelegate,UITableViewDataSource>{
    MovieInfo * _movieinfo;
    UITableView * _cinematable;
    
}

@property(nonatomic,retain)IBOutlet UITableView* cinematable;

@end

@interface MovieScheduleDelegate1: NSObject< TTURLRequestDelegate>{
    
    MovieScheduleController * _controller;
}

- (id)initWithController:(id *)controller;
@end
