//
//  MovieInfo.m
//  wirelessDemo
//
//  Created by Max Qian on 12/31/11.
//  Copyright (c) 2011 Cisco-Webex. All rights reserved.
//

#import "MovieInfo.h"

@implementation DataStore

@synthesize movie_info_array = _movie_info_array;
@synthesize cinema_info_array = _cinema_info_array;

+(DataStore *) SharedDataStore
{
    static DataStore * p = nil;
    if(p == nil)
    {
        p = [[DataStore alloc]init];
        p.movie_info_array = [[NSMutableArray array] retain];
        p.cinema_info_array = [[NSMutableArray array]retain];
    }
    return p;
}

@end

@implementation MovieInfo
@synthesize id = _id;
@synthesize name = _name;
@synthesize name_en = _name_en;
@synthesize director = _director;
@synthesize performers = _performers;
@synthesize category = _category;
@synthesize language_dub = _language_dub;
@synthesize language_subtitle = _language_subtitle;
@synthesize description = _description;
@synthesize duration = _duration;
@synthesize server_image_url = _server_image_url;
@synthesize local_image_url = _local_image_url;
@synthesize sample_video_url = _sample_video_url;
@synthesize comments = _comments;
@synthesize startDate = _startDate;
@synthesize score = _score;
@synthesize tempBitmap = _tempBitmap;
@synthesize status = _status;
@synthesize hasSchedule = _hasSchedule;
@synthesize movieSchedule = _movieSchedule;

@end

@implementation ScheduleInfo

@synthesize movieid = _movieid;
@synthesize moviename = _moviename;
@synthesize moviename_en = _moviename_en;
@synthesize movietime = _movietime;
@synthesize cinemaid = _cinemaid;
@synthesize screenid = _screenid;
@synthesize price = _price;
@synthesize dub = _dub;
@synthesize subtitle = _subtitle;

@end
