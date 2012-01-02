//
//  WeatherCell.h
//  wirelessDemo
//
//  Created by Nick Xiao on 1/2/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface WeatherCell : UITableViewCell
{
    UILabel *myWeekDay, *myTempHigh, *myTempLow;
    UIImageView *myWeatherIcon;
}

@property (retain) IBOutlet UILabel *weekDay, *tempHigh, *tempLow;
@property (retain) IBOutlet UIImageView *weatherIcon;


@end
