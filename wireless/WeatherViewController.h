//
//  WeatherViewController.h
//  wirelessDemo
//
//  Created by Nick Xiao on 1/2/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

@class WeatherDetailsController;

@interface WeatherViewController : UIViewController
{
    WeatherDetailsController* myWeatherDetailsController;
}

@property (retain) WeatherDetailsController* weatherDetailsController;
@end
