//
//  WeatherViewController.h
//  wirelessDemo
//
//  Created by Nick Xiao on 1/2/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

@class WeatherDetailsController;

@interface WeatherViewController : UIViewController<UITableViewDelegate, UITableViewDataSource>
{
    UILabel *myCity, *myCurrentTemp;
    UIImageView *myWeatherIcon;
    NSString* myCityID;
}

@property (retain) NSString* cityID;
@property (retain) IBOutlet UILabel *city, *currentTemp;
@property (retain) IBOutlet UIImageView *weatherIcon;
@property (retain) IBOutlet UITableView *weatherDetail;

- (NSString *)getDayOfTheWeek:(NSDate *)date;

@end
