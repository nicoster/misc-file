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
    NSString* myHDImage;
}

@property (retain) NSString* cityName;
@property (retain) NSString* cityID;


@property (retain) NSMutableArray* weathers;
@property (retain) NSMutableArray* tempHighs;
@property (retain) NSMutableArray* tempLows;
@property (retain) NSMutableArray* winds;
@property (retain) NSMutableArray* images;
@property (retain) NSString* HDImage;

@end

// {"weatherinfo":{"city":"苏州","cityid":"101190401","temp":"3","wd":"东北风","ws":"3级","sd":"68%","wse":"3","time":"22:30","isradar":"0","radar":""}}
@interface RealtimeWeatherData : NSObject {

}

@property (retain) NSString* cityName;
@property (retain) NSString* cityID;
@property (retain) NSString* currentTemp;
@property (retain) NSString* windDirection;
@property (retain) NSString* windSpeed;
@property (retain) NSString* humidity;
@property (retain) NSString* time;

@end

@protocol TTURLRequestDelegate
@end

@interface WeatherDataMgr : NSObject<TTURLRequestDelegate>
{
//    NSMutableDictionary* myData;
//    NSMutableDictionary* myRealtimeData;
}

+ (WeatherDataMgr*) sharedWeatherDataMgr;
- (void) retrieveData;
- (void) addCity:(NSString*) cityid;

@property (retain) NSMutableArray* normalWeatherRequest;
@property (retain) NSMutableDictionary* realtimeWeatherRequest;

@end
