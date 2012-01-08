//
//  WeatherDataMgr.m
//  wirelessDemo
//
//  Created by Nick Xiao on 1/7/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import "WeatherDataMgr.h"
#import <extThree20JSON/extThree20JSON.h>
#import <Three20/Three20.h>

//@interface WeatherData ()
//
//@property (retain) NSMutableArray* mutableWeathers;
//@property (retain) NSMutableArray* mutableTempHighs;
//@property (retain) NSMutableArray* mutableTempLows;
//@property (retain) NSMutableArray* mutableWinds;
//@property (retain) NSMutableArray* mutableImages;
//
//@end

@implementation WeatherData
@synthesize cityID = myCityID, cityName = myCityName;
@synthesize weathers = myWeathers, tempLows = myTempLows, tempHighs = myTempHighs, winds = myWinds, images = myImages;
//@synthesize mutableWinds = myWinds, mutableImages = myImages, mutableTempLows = myTempLows, mutableWeathers = myWeathers, mutableTempHighs = myTempHighs;
- (id) init
{
    self = [super init];
    if (self == nil) return nil;
    
    self.weathers = [NSMutableArray arrayWithCapacity:6];
    self.tempLows = [NSMutableArray arrayWithCapacity:6];
    self.tempHighs = [NSMutableArray arrayWithCapacity:6];
    self.winds = [NSMutableArray arrayWithCapacity:6];
    self.images = [NSMutableArray arrayWithCapacity:6];
    
    return self;
}

- (void) dealloc
{
    self.weathers = nil;
    self.tempHighs = nil;
    self.tempLows = nil;
    self.winds = nil;
    self.images = nil;
    [super dealloc];
}

- (NSString*) parseWeather: (NSString*) weather
{
    NSAssert(NO, @"implement parseWeather");
    return @"";
}

- (void)setWeathers:(NSArray *)weathers
{
    for (NSUInteger index = 0; index < weathers.count; ++ index) {
        NSString* image = [self parseWeather: [weathers objectAtIndex:index] ];
        [myImages insertObject: image atIndex: index];
    }
}

@end

@interface WeatherDataMgr ()
@property (retain) NSMutableDictionary* data;

@end

@implementation WeatherDataMgr

@synthesize data = myData;

+ (WeatherDataMgr*) shardWeatherDataMgr
{
    static WeatherDataMgr* wdmgr = nil;
    if (wdmgr == nil)
    {
        wdmgr = [[WeatherDataMgr alloc] init];
    }
    return wdmgr;
}


- (id)init
{
    self = [super init];
    if (self) {
        self.data = [NSMutableDictionary dictionaryWithCapacity:5];
    }
    
    return self;
}

- (void)dealloc
{
    self.data = nil;
    [super dealloc];
}

- (void) addCity:(NSString*) cityid
{
    [self.data setObject: @"" forKey:cityid];
}

- (NSString*) buildUrl
{
    if ([self.data count] == 0) return @"";
    
    NSMutableString* url = [NSMutableString stringWithString:@"http://res.88bx.com:8080/wirelesssz/RXService?cmd=25&weatherId="];
    for (NSString* cityid in self.data) {
        [url appendFormat:@"%@;", cityid];
    }
    return url;
}

- (void)retrieveData
{
    TTURLRequest* request = [TTURLRequest requestWithURL:[self buildUrl] delegate:self];
        
    request.cachePolicy = TTURLRequestCachePolicyNoCache;
    
    request.response = [[[TTURLJSONResponse alloc] init] autorelease];
    
    BOOL ret = [request send];
    NSLog(@"TTURLRequest.send:%d", ret);    
}


#pragma mark -
#pragma mark TTURLRequestDelegate

///////////////////////////////////////////////////////////////////////////////////////////////////
- (void)requestDidStartLoad:(TTURLRequest*)request {
    //    [_requestButton setTitle:@"Loading..." forState:UIControlStateNormal];
}

- (void)request:(TTURLRequest*)request didFailLoadWithError:(NSError*)error {
    
}

- (NSString*) parseTempHigh: (NSString*) temp
{
    NSRange range = [temp rangeOfString:@"℃~"];
    if (range.location == NSNotFound) return @"";
    return [temp substringToIndex:range.location];
}

- (NSString*) parseTempLow: (NSString*) temp
{
    NSRange range = [temp rangeOfString:@"℃~"];
    if (range.location == NSNotFound) return @"";
    NSRange range2 = [temp rangeOfString:@"℃" options:NSCaseInsensitiveSearch range: NSMakeRange(range.location + range.length, [temp length] - range.location - range.length)];
    if (range2.location == NSNotFound) return @"";
    return [temp substringWithRange:NSMakeRange(range.location + range.length, range2.location - range.location - range.length)];
}

///////////////////////////////////////////////////////////////////////////////////////////////////
- (void)requestDidFinishLoad:(TTURLRequest*)request {
    //    return;
    TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
    
    NSArray *entries = JsonResponse.rootObject;
    
    for (NSDictionary* entry in entries) {
        NSDictionary *details = [entry objectForKey:@"weatherinfo"];
        
        WeatherData * wd = [[[WeatherData alloc] init] autorelease];
        
        wd.cityName = [details objectForKey:@"city"];
        wd.cityID = [details objectForKey:@"cityid"];
        
        for (int i = 0; i < 6; i ++) 
        {
            [wd.weathers insertObject:[details objectForKey: [NSString stringWithFormat: @"weather%d", i + 1]] atIndex:i];
            
            [wd.tempHighs insertObject: [self parseTempHigh:[details objectForKey:[NSString stringWithFormat: @"temp%d", i + 1]]] atIndex:i];
            
            [wd.tempLows insertObject: [self parseTempLow:[details objectForKey:[NSString stringWithFormat: @"temp%d", i + 1]]] atIndex:i];

            [wd.winds insertObject:[details objectForKey: [NSString stringWithFormat: @"wind%d", i + 1]] atIndex:i];
        }
        [myData setObject:wd forKey:wd.cityID];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:@"kWeatherDataReady" object:wd];
    }

}

@end
