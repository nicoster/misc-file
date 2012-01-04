//
//  CinemaInfo.h
//  wirelessDemo
//
//  Created by Max Qian on 1/4/12.
//  Copyright (c) 2012 Cisco-Webex. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CinemaInfo : NSObject{
    NSString * _city;
    NSString * _area;
    
    NSNumber * _cinemaid;
    
    NSString * _cinemaname;
    
    NSNumber * _starlevel;
    NSNumber * _longitude;
    NSNumber * _latitude;
    
    NSString * _opentime;
    
    BOOL _park;
    
    NSString * _address;
    NSString * _busline;
    
    NSString * _description;
    NSString * _imageurl;
    NSString * _logourl;
    NSString * _telphone;
    NSString * _facilities;
    NSString * _restaurant;
    NSString * _entplace;
    
    NSNumber * _validfilmnumber;
    
}

@property (nonatomic, copy) NSString*   city;
@property (nonatomic, copy) NSString*   area;
@property (nonatomic, retain) NSNumber* cinemaid;
@property (nonatomic, copy) NSString*   cinemaname;
@property (nonatomic, retain) NSNumber* starlevel;
@property (nonatomic, retain) NSNumber* longitude;
@property (nonatomic, retain) NSNumber* latitude;
@property (nonatomic, copy) NSString*   opentime;
@property (nonatomic)  BOOL park;
@property (nonatomic, copy) NSString*   address;
@property (nonatomic, copy) NSString*   busline;
@property (nonatomic, copy) NSString*   description;
@property (nonatomic, copy) NSString*   imageurl;
@property (nonatomic, copy) NSString*   logourl;
@property (nonatomic, copy) NSString*   telphone;
@property (nonatomic, copy) NSString*   facilities;
@property (nonatomic, copy) NSString*   restaurant;
@property (nonatomic, copy) NSString*   entplace;
@property (nonatomic, retain) NSNumber * validfilmnumber;

@end
