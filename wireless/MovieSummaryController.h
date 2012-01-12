//
//  MovieSummaryController.h
//  wirelessDemo
//
//  Created by Max Qian on 12/22/11.
//  Copyright (c) 2011 Cisco-Webex. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FlowCoverView.h"
#import <Three20/Three20.h>
#import "MovieInfo.h"




@interface MovieSummaryController : UIViewController<FlowCoverViewDelegate>{

    FlowCoverView * _flow;
    
    UILabel * _movie_title;
    UILabel * _movie_director;
    UILabel * _movie_performers;
    UILabel * _movie_category;
    UILabel * _movie_duration;
    UILabel * _movie_startDate;
    
//    NSMutableArray * _movie_info_array;
//    NSMutableArray * _cinema_info_array;
    int _currentIdx;
}

//@property (nonatomic, retain) NSMutableArray* movie_info_array;
//@property (nonatomic, retain) NSMutableArray* cinema_info_array;
@property (nonatomic) int currentIdx;

@property(nonatomic,retain) IBOutlet FlowCoverView* flow;

@property(nonatomic,retain) IBOutlet UILabel* movie_title;
@property(nonatomic,retain) IBOutlet UILabel * movie_director;
@property(nonatomic,retain) IBOutlet UILabel * movie_performers;
@property(nonatomic,retain) IBOutlet UILabel * movie_category;
@property(nonatomic,retain) IBOutlet UILabel * movie_duration;
@property(nonatomic,retain) IBOutlet UILabel * movie_startDate;

- (void) UpdateUI;

- (IBAction)viewCinema;

@end

@interface MovieInfoDelegate: NSObject< TTURLRequestDelegate>{
    
    MovieSummaryController * _controller;
}
//@property(nonatomic, retain) MovieSummaryController *controller;

- (id)initWithController:(MovieSummaryController *)controller;
@end

@interface ImageDelegate: NSObject<TTURLRequestDelegate>{
    MovieSummaryController * _controller;
}

- (id)initWithController:(MovieSummaryController *)controller;
@end

@interface CinemaInfoDelegate : NSObject<TTURLRequestDelegate> {
    MovieSummaryController * _controller;
}
-(id)initWithController:(MovieSummaryController *)controller;
@end
