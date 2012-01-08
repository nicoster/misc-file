//
//  MovieScheduleDetailsController.h
//  wirelessDemo
//
//  Created by Max Qian on 1/8/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MovieScheduleController.h"

@interface MovieScheduleDetailsController : UIViewController<UITableViewDelegate,UITableViewDataSource, TTURLRequestDelegate>{
    
    UITableView * _moviescheduletable;
    UISegmentedControl * _datesegmented;
    
    MovieInCinema * _movieschedule;
}

@property(nonatomic, retain) IBOutlet UITableView * moviescheduletable;
@property(nonatomic, retain) IBOutlet UISegmentedControl * datesegmented;


- (IBAction)segmentControlAction:(id)sender;
@end
