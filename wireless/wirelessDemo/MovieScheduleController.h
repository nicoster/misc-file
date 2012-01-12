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
#import "MovieInfoController.h"

static NSString* moviescheduleRequestURLPath = @"http://res.88bx.com:8080/wirelesssz/RXService?token=970497ff485736e74c5460416fab0c14&cmd=15&city=320500&movieDay=%d&movieId=%d";

@interface MovieInCinema : NSObject {
    NSNumber * _movieid;
    NSNumber * _cinemaid;
    NSInteger _movieCount;
    NSInteger _day;
}

@property(nonatomic, retain) NSNumber *movieid;
@property(nonatomic, retain) NSNumber *cinemaid;
@property(nonatomic)    NSInteger day;
@property(nonatomic) NSInteger movieCount;
-(id) init;
@end


@interface MovieScheduleController : UIViewController<UITableViewDelegate,UITableViewDataSource, TTURLRequestDelegate>{
    MovieInfo * _movieinfo;
    UITableView * _cinematable;
    UISegmentedControl * _datesegmented;

    NSMutableArray * _cinematable_array;
    
    //UIView * _movieinfoview;
    UIButton * _button;
    MovieInfoController *_movieinfoController;
}
@property (nonatomic, retain) MovieInfo * movieinfo;

@property(nonatomic,retain)IBOutlet UITableView* cinematable;

@property(nonatomic,retain)IBOutlet UISegmentedControl* datesegmented;

@property(nonatomic, retain) NSMutableArray * cinematable_array;

@property(nonatomic, retain) IBOutlet UIButton * mybutton;
@property(nonatomic, retain) MovieInfoController *movieinfoController;

-(void)sendRequest: (NSInteger)day movieid:(NSInteger )id;

- (IBAction)segmentControlAction:(id)sender;
-(IBAction)buttonSwitch:(id)sender;



@end


