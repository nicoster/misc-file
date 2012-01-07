//
//  MovieInfo.h
//  wirelessDemo
//
//  Created by Max Qian on 12/31/11.
//  Copyright (c) 2011 Cisco-Webex. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DataStore : NSObject {
@private
    NSMutableArray * _movie_info_array;
    NSMutableArray * _cinema_info_array;
}
@property (nonatomic, retain) NSMutableArray* movie_info_array;
@property (nonatomic, retain) NSMutableArray* cinema_info_array;
+(DataStore *) SharedDataStore;

@end

@interface MovieInfo : NSObject{
    
    NSNumber *  _id;
    
    NSString *  _name;
    NSString *  _name_en;
    NSString *  _director;
    NSString *  _performers;
    NSString *  _category;
    NSString *  _language_dub;
    NSString *  _language_subtitle;
    NSString *  _description;
        
    NSNumber *  _duration;
    
    NSString *  _server_image_url;
    NSString *  _local_image_url;
    NSString *  _sample_video_url;
    NSString *  _comments;
    
    NSDate *    _startDate;
    
    NSNumber *  _score;
    
    UIImage *   _tempBitmap;
    
    NSNumber *  _status; // 0-已经上映  1-upcoming
    
    NSMutableDictionary * _hasSchedule;
    
    NSMutableArray * _movieSchedule;
    
}

@property (nonatomic, retain) NSNumber*   id;
@property (nonatomic, copy) NSString*   name;
@property (nonatomic, copy) NSString*   name_en;
@property (nonatomic, copy) NSString*   director;
@property (nonatomic, copy) NSString*   performers;
@property (nonatomic, copy) NSString*   category;
@property (nonatomic, copy) NSString*   language_dub;
@property (nonatomic, copy) NSString*   language_subtitle;
@property (nonatomic, copy) NSString*   description;
@property (nonatomic, retain) NSNumber*   duration;
@property (nonatomic, copy) NSString*   server_image_url;
@property (nonatomic, copy) NSString*   local_image_url;
@property (nonatomic, copy) NSString*   sample_video_url;
@property (nonatomic, copy) NSString*   comments;
@property (nonatomic, retain) NSDate*   startDate;
@property (nonatomic, retain) NSNumber*   score;
@property (nonatomic, retain) UIImage*   tempBitmap;
@property (nonatomic, retain) NSNumber*   status;
@property (nonatomic, retain) NSMutableDictionary*   hasSchedule;
@property (nonatomic, retain) NSMutableArray*   movieSchedule;
@end

@interface ScheduleInfo : NSObject {
    /*
     private Date movieTime;
     private int movieId;
     private String movieName;
     private String movieName_en;
     private int cinemaId;
     private int screenId;
     private int price;
     
     private String dub; // 对话
     private String subtitle;// 字幕
     
     public ExchangeTicket[] tickets;
     */
    NSDate * _movietime;
    NSNumber * _movieid;
    NSString * _moviename;
    NSString * _moviename_en;
    NSNumber * _cinemaid;
    NSNumber * _screenid;
    NSNumber * _price;
    NSString * _dub;
    NSString * _subtitle;
    
}
@property (nonatomic, retain) NSDate* movietime;
@property (nonatomic, retain) NSNumber * movieid;
@property (nonatomic, copy) NSString * moviename;
@property (nonatomic, copy) NSString * moviename_en;
@property (nonatomic, retain) NSNumber * cinemaid;
@property (nonatomic, retain) NSNumber * screenid;
@property (nonatomic, retain) NSNumber * price;
@property (nonatomic, copy) NSString * dub;
@property (nonatomic, copy) NSString * subtitle;
@end
