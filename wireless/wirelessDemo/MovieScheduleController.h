//
//  MovieScheduleController.h
//  wirelessDemo
//
//  Created by Max Qian on 1/6/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "MovieInfo.h"
#import "CinemaInfo.h" 
#import <Three20/Three20.h>

@interface MovieInCinema : NSObject {
    NSNumber * _movieid;
    NSNumber * _cinemaid;
    NSInteger _movieCount;
    NSMutableArray * _moviescheduledetails_array;
}

@property(nonatomic, retain) NSNumber *movieid;
@property(nonatomic, retain) NSNumber *cinemaid;
@property(nonatomic, retain) NSMutableArray * moviescheduledetails_array;
@property(nonatomic) NSInteger movieCount;
-(id) init;
@end


@interface MovieScheduleController : UIViewController<UITableViewDelegate,UITableViewDataSource, TTURLRequestDelegate>{
    MovieInfo * _movieinfo;
    UITableView * _cinematable;
    UISegmentedControl * _datesegmented;

    NSMutableArray * _cinematable_array;
    
}
@property (nonatomic, retain) MovieInfo * movieinfo;

@property(nonatomic,retain)IBOutlet UITableView* cinematable;

@property(nonatomic,retain)IBOutlet UISegmentedControl* datesegmented;

@property(nonatomic, retain) NSMutableArray * cinematable_array;

- (IBAction)segmentControlAction:(id)sender;

@end


