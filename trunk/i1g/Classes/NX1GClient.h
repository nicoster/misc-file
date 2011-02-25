//
//  NX1GClient.h
//  iPhoneStreamingPlayer
//
//  Created by Nick Xiao on 2/21/11.
//  Copyright 2011 Cisco CSG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NXHttpClient.h"

typedef enum _SongListType {
	SLT_GIVEN,
	SLT_NEXT,
	SLT_SEARCH,
	SLT_MAX,
}SongListType;

typedef enum _CallType
{
	CT_LISTSONG,
	CT_LOGIN = SLT_MAX,
	CT_LYRIC,
	CT_COMMENT,
	CT_CLIENTINFO,
	CT_TRACK,
	CT_LOADSHOW,
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

@end


@interface NX1GClient : NSObject<NXHttpClientDelegate> {
	
	NSMutableArray *songs, *givenIds, *playList;
	NSString *magic;
}

@property (nonatomic, retain, readonly) NSMutableArray* songs;
@property (nonatomic, retain, readwrite) NSMutableArray *playList;

+ (NX1GClient*) shared1GClient;

- (void) connection: (HttpConnectionId)connection didFinishWithData: (NSData*) data andError: (NSError*) error andUserData: (id) userData; 

- (void) listSongsByType: (SongListType) type;
- (void) loginWithUser: (NSString*) user andPassword: (NSString*) passwd;
- (void) loadLyricWithId: (int) songId;
- (void) loadCommentWithTitle: (NSString*) title;

@end
