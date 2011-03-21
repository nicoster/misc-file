//
//  NX1GClient.h

//
//  Created by Nick Xiao on 2/21/11.
//  Copyright 2011 Cisco CSG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NXHttpClient.h"


#define PLAYLISTSIZE 10

typedef enum _SongListType {
	SLT_GIVEN,
	SLT_NEXT,
	SLT_POOL,
	SLT_TAG,
	SLT_SEARCH,
	SLT_MAX,
}SongListType;

typedef enum _CallType
{
	CT_LISTSONG,
	CT_LOGIN = SLT_MAX - SLT_GIVEN,
	CT_LYRIC,
	CT_COMMENT,
	CT_CLIENTINFO,
	CT_TRACK,
	CT_LOADSHOW,
	CT_FAV,
	CT_LOGOUT,
}CallType;

@interface NXSongUrl : NSObject
{
	NSString *urlId, *format, *url;
	int size;
}

@property (nonatomic, retain, readwrite) NSString *urlId, *format, *url;
@property (nonatomic, assign, readwrite) int size;


@end


@interface NXSong : NSObject
{
	NSString *title, *songId, *singer, *album, *remark, *uploader, *collector;
	NSMutableArray *urls;
}

@property (nonatomic, retain, readwrite) NSString *title, *songId, *singer, *album, *remark, *uploader, *collector;
@property (nonatomic, retain, readwrite) NSMutableArray *urls;

- (NSArray*) urlArray;

@end


@interface NX1GClient : NSObject<NXHttpClientDelegate> {
	
	NSMutableArray *songs, *playList, *searchResults, *history, *fav;
	NSString *magic;
}

@property (nonatomic, retain, readwrite) NSMutableArray *songs, *searchResults, *history, *playList, *fav;

+ (NX1GClient*) shared1GClient;

- (void) saveGivenIds;

- (void) connection: (HttpConnectionId)connection didFinishWithData: (NSData*) data andError: (NSError*) error andUserData: (id) userData; 

- (int) songsByType: (SongListType) type withCriteria: (NSString*) criteria;
- (int) loginWithUser: (NSString*) user andPassword: (NSString*) passwd;
- (void) loadLyricWithId: (NSString*) songId;
- (void) loadCommentWithTitle: (NSString*) title;
- (void) favById: (NSString*) songId;
- (int) logout;
- (bool) isFav: (NSString*) songId;

@end
