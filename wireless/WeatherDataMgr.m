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



@interface NSMutableString (wireless)
- (BOOL) eat: (NSString*) str;
@end

@implementation NSMutableString (wireless)
- (BOOL) eat: (NSString*) str
{
    NSRange range = [self rangeOfString: str];
    if(range.location != NSNotFound)
    {
        [self replaceCharactersInRange:range withString: @"@"];
        return YES;
    }
    return NO;
}

@end

@implementation WeatherData
@synthesize cityID = myCityID, cityName = myCityName;
@synthesize weathers = myWeathers, tempLows = myTempLows, tempHighs = myTempHighs, winds = myWinds, images = myImages, HDImage = myHDImage;
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


//- (void)setWeathers:(NSArray *)weathers
//{
//    for (NSUInteger index = 0; index < weathers.count; ++ index) {
//        NSString* image = [self parseWeather: [weathers objectAtIndex:index] ];
//        [myImages insertObject: image atIndex: index];
//    }
//}

@end


@implementation RealtimeWeatherData

@synthesize cityName = myCityName, cityID = myCityID, currentTemp = myCurrentTemp, windDirection = myWindDirection, windSpeed = myWindSpeed, humidity = myHumidity, time = myTime;

@end

@interface WeatherDataMgr ()
@property (retain) NSMutableDictionary* data;
@property (retain) NSMutableDictionary* realtimeWeather;
@end

@implementation WeatherDataMgr
@synthesize normalWeatherRequest = myNormalWeatherRequest, realtimeWeatherRequest = myRealtimeWeatherRequest;

@synthesize data = myData, realtimeWeather = myRealtimeWeather;

+ (WeatherDataMgr*) sharedWeatherDataMgr
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
        self.data = [NSMutableDictionary dictionaryWithCapacity:6];
        self.realtimeWeather = [NSMutableDictionary dictionaryWithCapacity:3];
        self.normalWeatherRequest = [NSMutableArray arrayWithCapacity:2];
        self.realtimeWeatherRequest = [NSMutableDictionary dictionaryWithCapacity:3];
    }
    
    return self;
}

- (void)dealloc
{
    self.data = nil;
    self.realtimeWeather = nil;
    [super dealloc];
}

- (void) addCity:(NSString*) cityid
{
    [self.data setObject: @"" forKey:cityid];
}


- (NSString*) matchHDImage: (NSString*) normalizedWeather 
{
    static NSArray* images = nil;
    if (images == nil)
    {
        images = [NSArray arrayWithObjects:
                        @"overcast",
                       @"overcastdust",
                       @"rainbig",
                       @"rainovercast",
                       @"rainovercastbig",
                       @"rainsmall",
                       @"snow",
                       @"sun",
                       @"suncloud",
                       @"suncloudsmall",
                       @"sundust",
                       @"sunlightening",
                       @"sunrainbig",
                       @"sunrainsmall",
                       @"unknown",
                       @"cloudovercast",
                       @"fog",
                       @"lightening",                   
                       nil];
    }
    
    NSString* trimedWeather = [normalizedWeather stringByReplacingOccurrencesOfString:@":" withString:@""];
    for (NSString* image in images)
    {
        NSRange range = [image rangeOfString: trimedWeather];
        if (range.location != NSNotFound)
        {
            return image;
        }
            
    }
    return @"";
}

- (NSString*) matchSmallImage: (NSString*) normalizedWeather 
{
    static NSArray* images = nil;
    if (images == nil)
    {
        images = [NSArray arrayWithObjects:
                  @"clearnight",
                  @"cloud",
                  @"flurries",
                  @"fog",
                  @"hail",
                  @"ice",
                  @"lightening",
                  @"overcast",
                  @"rain",
                  @"raincloud",
                  @"rainsnow",
                  @"snow",
                  @"sun",
                  @"suncloud",
                  @"sunhaze",
                  @"sunrain",
                  @"wind",
                  nil];
    }
    
    NSString* trimedWeather = [normalizedWeather stringByReplacingOccurrencesOfString:@":" withString:@""];
    for (NSString* image in images)
    {
        NSRange range = [image rangeOfString: trimedWeather];
        if (range.location != NSNotFound)
        {
            return image;
        }
        
    }
    return @"";
}

- (NSString*) trimLastSegment: (NSString*) normalizedWeather
{
    NSRange range = [normalizedWeather rangeOfString:@":" options:NSBackwardsSearch];
    if (range.location != NSNotFound) {
        return [normalizedWeather substringToIndex:range.location];
    }
    return @"";
}

- (NSString*) parseWeather: (NSString*) aWeather withHDImage: (BOOL) HDImage
{
    NSMutableString* weather = [NSMutableString stringWithString:aWeather];
    NSString *ret = @"";
    for (int i = 0; i < 2; ++ i) 
    {
        if ([weather eat:@"晴"])
        {
            ret = [NSString stringWithFormat:@"%@:sun", ret];
        }
        else if ([weather eat:@"雨"])
        {
            ret = [NSString stringWithFormat:@"%@:rain", ret];
        }
        else if ([weather eat:@"云"])
        {
            ret = [NSString stringWithFormat:@"%@:cloud", ret];
        }
        else if ([weather eat:@"雪"])
        {
            ret = [NSString stringWithFormat:@"%@:snow", ret];
        }
        else if ([weather eat:@"阴"])
        {
            ret = [NSString stringWithFormat:@"%@:overcast", ret];
        }
        else if ([weather eat:@"电"])
        {
            ret = [NSString stringWithFormat:@"%@:lightening", ret];
        }
        else if ([weather eat:@"雾"])
        {
            ret = [NSString stringWithFormat:@"%@:fog", ret];
        }
        else if ([weather eat:@"尘"])
        {
            ret = [NSString stringWithFormat:@"%@:dust", ret];
        }
    }
    
    if ([weather eat:@"大"])
    {
        ret = [NSString stringWithFormat:@"%@:big", ret];
    }
    else if ([weather eat:@"小"])
    {
        ret = [NSString stringWithFormat:@"%@:small", ret];        
    }
    
    if ([ret length] == 0)
    {
        return @"unknown";
    }
    
    while ([ret length])
    {
        NSString* image = HDImage ? [self matchHDImage:ret] : [self matchSmallImage:ret];
        if ([image length]) 
        {
            return image;
        }
        
        ret = [self trimLastSegment:ret];
    }
    
    return @"unknown";
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

- (NSString*) buildRealtimeWeatherUrl: (NSString*) cityId
{
    if ([cityId length] == 0) return @"";
    return [NSString stringWithFormat:@"http://res.88bx.com:8080/wirelesssz/RXService?cmd=26&weatherId=%@", cityId];
}


- (void)retrieveData
{
    {
        TTURLRequest* request = [[TTURLRequest requestWithURL:[self buildUrl] delegate:self] autorelease];
        [request retain];
        [self.normalWeatherRequest insertObject:request.urlPath atIndex:0];
        [self.normalWeatherRequest insertObject:[NSDate date] atIndex:1];
            
        request.cachePolicy = TTURLRequestCachePolicyNoCache;
        request.response = [[[TTURLJSONResponse alloc] init] autorelease];
        
        BOOL ret = [request send];
        NSLog(@"TTURLRequest.send:%d", ret);    
    }
    
    for (NSString* cityId in self.data) 
    {
        TTURLRequest* request = [[TTURLRequest requestWithURL:[self buildRealtimeWeatherUrl:cityId] delegate:self] autorelease];
        [request retain];
        [self.realtimeWeatherRequest setObject:[NSDate date] forKey:request.urlPath];
        
        request.cachePolicy = TTURLRequestCachePolicyNoCache;
        request.response = [[[TTURLJSONResponse alloc] init] autorelease];
        
        BOOL ret = [request send];
        NSLog(@"TTURLRequest.send:%d", ret);    
        
    }
    

}


#pragma mark -
#pragma mark TTURLRequestDelegate

///////////////////////////////////////////////////////////////////////////////////////////////////
- (void)requestDidStartLoad:(TTURLRequest*)request {
    //    [_requestButton setTitle:@"Loading..." forState:UIControlStateNormal];
}

- (void)request:(TTURLRequest*)request didFailLoadWithError:(NSError*)error {
    NSLog(@"%@", [error debugDescription]);
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
    NSLog(@"requestDidFinishLoad");    
    
    if ([request.urlPath isEqualToString: [self.normalWeatherRequest objectAtIndex:0]])
    {
        TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
        
        NSArray *entries = JsonResponse.rootObject;
        
        for (NSDictionary* entry in entries) {
            NSDictionary *details = [entry objectForKey:@"weatherinfo"];
            
            WeatherData * wd = [[[WeatherData alloc] init] autorelease];
            
            wd.cityName = [details objectForKey:@"city"];
            wd.cityID = [details objectForKey:@"cityid"];
            
            for (int i = 0; i < 6; i ++) 
            {
                NSString* weather = [details objectForKey: [NSString stringWithFormat: @"weather%d", i + 1]];
                if (i == 0)
                {
                    wd.HDImage = [NSString stringWithFormat:@"%@.png", [self parseWeather: weather withHDImage:YES]];
                }
                
                NSString* image = [NSString stringWithFormat:@"mini-%@.png", [self parseWeather: weather withHDImage:NO]];
                [wd.images insertObject:image atIndex:i];
                [wd.weathers insertObject:weather atIndex:i];
                
                [wd.tempHighs insertObject: [self parseTempHigh:[details objectForKey:[NSString stringWithFormat: @"temp%d", i + 1]]] atIndex:i];
                
                [wd.tempLows insertObject: [self parseTempLow:[details objectForKey:[NSString stringWithFormat: @"temp%d", i + 1]]] atIndex:i];

                [wd.winds insertObject:[details objectForKey: [NSString stringWithFormat: @"wind%d", i + 1]] atIndex:i];
            }
            [self.data setObject:wd forKey:wd.cityID];
            
            [[NSNotificationCenter defaultCenter] postNotificationName:@"kWeatherDataReady" object:wd];
        }
        
        [self.normalWeatherRequest insertObject:@"" atIndex:0];
    }
    else         
    {
        if([self.realtimeWeatherRequest objectForKey:request.urlPath])
        {
            TTURLJSONResponse *JsonResponse = (TTURLJSONResponse*)request.response;
            // {"weatherinfo":{"city":"苏州","cityid":"101190401","temp":"3","wd":"东北风","ws":"3级","sd":"68%","wse":"3","time":"22:30","isradar":"0","radar":""}}
            NSDictionary* details = [JsonResponse.rootObject objectForKey: @"weatherinfo"];
            RealtimeWeatherData* rwd = [[[RealtimeWeatherData alloc] init] autorelease];
            rwd.cityName = [details objectForKey: @"city"];
            rwd.cityID = [details objectForKey: @"cityid"];
            rwd.currentTemp = [details objectForKey: @"temp"];
            rwd.windDirection = [details objectForKey: @"wd"];
            rwd.windSpeed = [details objectForKey: @"ws"];
            rwd.humidity = [details objectForKey: @"sd"];
            rwd.time = [details objectForKey: @"time"];
            
            [self.realtimeWeather setObject:rwd forKey:rwd.cityID];
            [[NSNotificationCenter defaultCenter] postNotificationName:@"kRealtimeWeatherDataReady" object:rwd];
            
            [self.realtimeWeatherRequest removeObjectForKey:request];
        }
        else
        {
            NSLog(@"warning. unknown request:%@", [request urlPath]);
        }
    }
    
}

@end
