//
//  WeatherSummaryController.h
//  wirelessDemo
//
//  Created by Nick Xiao on 1/2/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//



@interface WeatherSummaryController : UIViewController<UIScrollViewDelegate>
{

    NSMutableArray* myWeathers;
    IBOutlet UIScrollView* myScrollView;
    IBOutlet UIPageControl* pageControl;
}

@property (nonatomic, retain) NSMutableArray* weathers;
@property (retain) UIScrollView* scrollView;
@property (nonatomic, retain) UIPageControl* pageControl;

@end
