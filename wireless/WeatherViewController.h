//
//  WeatherViewController.h
//  wirelessDemo
//
//  Created by Nick Xiao on 1/2/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

@class WeatherDetailsController;

@class WeatherData;
@class RealtimeWeatherData;

@interface WeatherViewController : UIViewController<UITableViewDelegate, UITableViewDataSource>
{
    UILabel *myCity, *myCurrentTemp, *myWeatherDesc;
    UIImageView *myWeatherIcon;
    NSString* myCityID;
    WeatherData* myWeatherData;
}

@property (retain) NSString* cityID;
@property (retain) IBOutlet UILabel *city;
@property (retain) IBOutlet UILabel *currentTemp;
@property (retain) IBOutlet UILabel *weatherDesc;
@property (retain) IBOutlet UIImageView *weatherIcon;
@property (retain) IBOutlet UITableView *weatherDetail;
@property (retain) WeatherData* weatherData;
@property (retain) RealtimeWeatherData* realtimeWeatherData;

- (NSString *)getDayOfTheWeek:(NSDate *)date;
- (void)onWeatherDataReady: (NSNotification*) note;

@end
