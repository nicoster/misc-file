//
//  WeatherDataMgr.h
//  wirelessDemo
//
//  Created by Nick Xiao on 1/7/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface WeatherData : NSObject {

    NSString* myCityName;
    NSString* myCityID;
    NSMutableArray* myWeathers;
    NSMutableArray* myTempHighs;
    NSMutableArray* myTempLows;
    NSMutableArray* myWinds;
    NSMutableArray* myImages;
}

@property (retain) NSString* cityName;
@property (retain) NSString* cityID;


@property (retain) NSMutableArray* weathers;
@property (retain) NSMutableArray* tempHighs;
@property (retain) NSMutableArray* tempLows;
@property (retain) NSMutableArray* winds;
@property (retain) NSMutableArray* images;

@end

@protocol TTURLRequestDelegate
@end

@interface WeatherDataMgr : NSObject<TTURLRequestDelegate>
{
    NSMutableDictionary* myData;
}

+ (WeatherDataMgr*) shardWeatherDataMgr;
- (void) retrieveData;
- (void) addCity:(NSString*) cityid;
@end
