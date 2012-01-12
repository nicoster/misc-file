//
//  CinemaDetailInfoController.h
//  wirelessDemo
//
//  Created by Max Qian on 1/11/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CinemaInfo.h"

@interface CinemaDetailInfoController : UIViewController<UITableViewDelegate,UITableViewDataSource>{
    
    UILabel * _cinemaname;
    UITableView * _cinemaDetailtable;
    
    NSNumber * _cinemaid;
    CinemaInfo * _cinemainfo;
}
@property (retain, nonatomic) IBOutlet UILabel *cinemaname;
@property (retain, nonatomic) NSNumber * cinemaid;
@property (retain, nonatomic) IBOutlet UITableView * cinemaDetailtable;
@end
