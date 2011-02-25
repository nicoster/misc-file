//
//  NX1GClient.m
//  iPhoneStreamingPlayer
//
//  Created by Nick Xiao on 2/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NX1GClient.h"
#import "NXHttpClient.h"
#import <stdlib.h>	// arc4random()

#include "GDataXMLNode.h"

#define PLAYLISTSIZE 10



NSString* URL_LISTSONG = @"http://www.1g1g.com/list/load.jsp?type=%@";
NSString* DATA_LISTSONG = @"givenids=%@&preferredstore=2&start=0&uniqueCode=%d&type=%@&number=50&encoding=utf8&magic=%@";
NSString* URL_LOGIN = @"http://www.1g1g.com/user/account.jsp";
NSString* URL_LYRIC = @"http://www.1g1g.com/list/lyric.jsp";
NSString* URL_COMMENT = @"http://www.1g1g.com/report/getComment.jsp";
NSString* URL_CLIENTINFO = @"http://www.1g1g.com/info/clientinfo.jsp";
NSString* URL_TRACK = @"http://www.1g1g.com/report/track.jsp";
NSString* URL_LOADSHOW = @"http://www.1g1g.com/info/loadingshow.jsp?lastid=%d";

@interface GDataXMLElement(NX)
- (NSString*) stringForName: (NSString*) key;
@end

@implementation GDataXMLElement(NX)

- (NSString*) stringForName: (NSString*) name {
	NSArray *items = [self elementsForName: name];
	for(GDataXMLElement *item in items) {
		return item.stringValue;
	}
	return nil;
}

//- (NSArray*) stringsForName: (NSString*) name andSubName: (NSString*)subName{
//	NSArray *items = [self elementsForName: name];
//	NSMutableArray * strings = [NSMutableArray arrayWithCapacity:[items count]];
//	for(GDataXMLElement *item in items) {
//		[strings addObject:item.stringValue];
//	}
//	return strings;
//}

@end


@implementation NXSong

@synthesize title, songId, singer, album, remark, uploader, collector, urls;

@end

@implementation NXSongUrl

@synthesize urlId, format, size, url;

@end



@interface NX1GClient()
@property (nonatomic, assign, readonly) NXHttpClient* httpClient;
@property (nonatomic, retain, readwrite) NSString* magic;
@property (nonatomic, retain, readwrite) NSArray* givenIds;
@property (nonatomic, retain, readwrite) NSMutableArray* songs;
@end

@implementation NX1GClient

@synthesize magic, givenIds, songs, playList;

+ (NX1GClient*) shared1GClient
{
	static NX1GClient* client = nil;
	@synchronized (client)
	{
		if (client == nil)
			client = [[NX1GClient alloc] init];
	}
	return client;
}

- (NXHttpClient*) httpClient {
	return [NXHttpClient sharedHttpClient];
}	

- (void) listSongsByType: (SongListType) type {
	if ([self.givenIds count] == 0) {
		type = SLT_NEXT;
	}
	static NSString* types[] = {@"given", @"next", @"search"};
	NSString* typestr = types[type];
	NSString* url = [NSString stringWithFormat:URL_LISTSONG, typestr];
	
	NSString* data = [NSString stringWithFormat: DATA_LISTSONG, @"", arc4random() * 0xffffffff, typestr, magic];
	
	[self.httpClient connect: url withDelegate:self andPostData: data andUserData: [NSNumber numberWithInt: CT_LISTSONG + type]];
}
- (void) loginWithUser: (NSString*) user andPassword: (NSString*) passwd {
}
- (void) loadLyricWithId: (int) songId {
}
- (void) loadCommentWithTitle: (NSString*) title {
	
}

- (NSString*) calculateMagic: (NSString*) seed
{
	int loc5 = 0;
	int loc1 = 17;
	int loc2 = 604373598;
	int loc3 = 0;
	int loc4 = [seed intValue];
	int loc6 = 0;
	while (loc6 < loc1)
	{
		loc5 = loc4 & 1;
		loc4 = loc4 >> 1 | loc5 << 31;
		loc3 = (loc3 + (loc2 ^ loc4)) & 0xFFFFFFFFF;
		++loc6;
	}
	/*if(loc3<0)
	 {
	 loc3 = -((~loc3 + 1) & 0xFFFFFFFF);
	 }*/
	return [NSString stringWithFormat:@"%d", loc3];
}


	

- (void) connection: (HttpConnectionId)connection didFinishWithData: (NSData*) data andError: (NSError*) error andUserData: (id) userData {
	int type = [(NSNumber*)userData intValue];
	if (error != nil)
	{
		NSLog(@"http, type:%d, err:%@", type, [error localizedDescription]);
		return;
	}
	
	NSString *string = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
	NSLog(@"http, done, %@", string);
	
	GDataXMLDocument *doc = [[GDataXMLDocument alloc] initWithData:data options:0 error:nil];
	NSString *resultCode = nil;
	NSArray *items = [doc nodesForXPath:@"/info/result" error:nil];
	for (GDataXMLElement *item in items) {
		GDataXMLNode* attrib = [item attributeForName:@"resultCode"];
		resultCode = attrib.stringValue; //[NSString stringWithFormat: [attrib stringValue]];
		break;
	}

	// 3240 3241, magic number is wrong
	if ([resultCode hasPrefix: @"324"]) {
		NSArray *items = [doc nodesForXPath:@"/info/seed" error:nil];
		for (GDataXMLElement *item in items) {
			self.magic = [self calculateMagic: item.stringValue];
			break;
		}
		
		[self listSongsByType:type];	// retry to list songs
		return;
	}
	
	switch (type) {
		case CT_LISTSONG + SLT_GIVEN:
		case CT_LISTSONG + SLT_NEXT:
		{	
			NSArray * items = [doc nodesForXPath:@"/info/songlist/song" error:nil];
			for (GDataXMLElement *item in items) {
				NXSong *song = [[NXSong alloc] init];
				
				song.title = [item stringForName:@"name"];
				song.singer = [item stringForName:@"singer"];
				song.uploader = [item stringForName:@"uploadinguser"];
				song.collector = [item stringForName:@"collectinguser"];
				song.album = [item stringForName:@"album"];
				song.songId = [item stringForName:@"id"];
				
				NSArray* srcs = [item elementsForName:@"source"];
				for (GDataXMLElement* src in srcs) {
					NSArray *urls = [src elementsForName:@"link"];
					for (GDataXMLElement* url in urls) {
						NXSongUrl *aUrl = [[NXSongUrl alloc] init];
						aUrl.format = [[url attributeForName:@"format"] stringValue];
						aUrl.urlId = [[url attributeForName:@"id"] stringValue];
						aUrl.url = url.stringValue;
						aUrl.size = [[[url attributeForName:@"filesize"] stringValue] intValue];
						if (song.urls)
							[song.urls addObject: aUrl];
						else {
							song.urls = [NSMutableArray arrayWithObject:aUrl];
						}

						[aUrl release];
					}
					break;
					
				}
				if ([self.playList count] < PLAYLISTSIZE)
				{
					if (self.playList) {
						[self.playList addObject: song];
					}
					else {
						self.playList = [NSMutableArray arrayWithObject: song];
					}
					
				}
				else
				{
					if (self.songs)
					{
						[self.songs addObject: song];
					}
					else {
						self.songs = [NSMutableArray arrayWithObject:song];
					}
				}

				[song release];
			
			}
			
			for (int i = 0; i < PLAYLISTSIZE; i ++) {

			}
			
			[[NSNotificationCenter defaultCenter] postNotificationName:@"SONG_LOADED" object:nil];
			[doc release];
			
			break;
		}
		case CT_LISTSONG + SLT_SEARCH:
		{
			break;
		}
		default:
			break;
	}

}


@end


