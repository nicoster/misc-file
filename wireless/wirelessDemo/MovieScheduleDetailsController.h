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
    
    NSMutableArray * _movieschedule_array;
}

@property(nonatomic, retain) IBOutlet UITableView * moviescheduletable;
@property(nonatomic, retain) IBOutlet UISegmentedControl * datesegmented;

@property(nonatomic, retain) NSMutableArray * movieschedule_array;

-(void)sendRequest: (NSInteger)day movieid:(NSInteger )id;
- (IBAction)segmentControlAction:(id)sender;
@end
