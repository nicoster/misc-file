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




NSString* URL_LISTSONG = @"http://www.1g1g.com/list/load.jsp?type=%@";
NSString* DATA_GIVENSONGS = @"givenids=%@&preferredstore=2&start=0&uniqueCode=%d&type=%@&number=50&encoding=utf8&magic=%@";
NSString* DATA_NEXTSONGS = @"preferredstore=2&start=0&uniqueCode=%d&type=%@&number=50&encoding=utf8&magic=%@";
NSString* DATA_SEARCHSONGS = @"username=nickx&query=%@&preferredstore=2&start=0&uniqueCode=%d&type=%@&number=130&encoding=utf8&magic=%@";
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

- (NSArray*) urlArray
{
	if ([urls count] == 0) {
		return nil;
	}
	
	NSMutableArray* array = [NSMutableArray array];
	for (NXSongUrl* url in urls)
	{
		[array addObject:[url url]];
	}
	return array;
}

@end

@implementation NXSongUrl

@synthesize urlId, format, size, url;

@end



@interface NX1GClient()
@property (nonatomic, assign, readonly) NXHttpClient* httpClient;
@property (nonatomic, retain, readwrite) NSString* magic;
@end

@implementation NX1GClient

@synthesize magic, songs, playList, searchResults, history;

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

- (id)init
{
	self = [super init];
	self.magic = @"";
	self.playList = [NSMutableArray arrayWithCapacity:PLAYLISTSIZE];
	self.songs = [NSMutableArray arrayWithCapacity:PLAYLISTSIZE * 3];
	return self;
}

- (void)dealloc
{
	magic = nil;
	songs = playList = nil;
	[super dealloc];
}

- (NXHttpClient*) httpClient {
	return [NXHttpClient sharedHttpClient];
}	

- (void) saveGivenIds
{
	NSMutableString * givenIds = nil;
	for (NXSong *song in self.playList) {
		if (givenIds) {
			[givenIds appendFormat:@",%@", song.songId];
		}
		else {
			givenIds = [NSMutableString stringWithString:song.songId];
		}
	}
	
	for (NXSong *song in self.songs) {
		if (givenIds) {
			[givenIds appendFormat:@",%@", song.songId];
		}
		else {
			givenIds = [NSMutableString stringWithString:song.songId];
		}
	}
	
	[[NSUserDefaults standardUserDefaults] setObject:givenIds forKey:@"kNX1GClientGivenIds"];
}

- (int) listSongsByType: (SongListType) type withCriteria: (NSString*) criteria {
	if ([criteria length] == 0 && type == SLT_SEARCH) {
		NSLog(@"try to search nothing, ignored.");
		return 0;
	}
	
	NSMutableString * givenIds = nil;
	if (type == SLT_GIVEN) {
		givenIds = [[NSUserDefaults standardUserDefaults] objectForKey:@"kNX1GClientGivenIds"];

		if ([givenIds length] == 0)
			type = SLT_NEXT;
	}
	static NSString* types[] = {@"given", @"next", @"pool"};
	NSString* theType = types[type];
	NSString* url = [NSString stringWithFormat:URL_LISTSONG, theType];
	NSString* data = nil;
	
	switch (type) {
		case SLT_GIVEN:
			data = [NSString stringWithFormat: DATA_GIVENSONGS, givenIds, arc4random() * 0xffffffff, theType, magic];
			break;
		case SLT_NEXT:
			data = [NSString stringWithFormat: DATA_NEXTSONGS, arc4random() * 0xffffffff, theType, magic];
			break;
		case SLT_SEARCH:
			data = [NSString stringWithFormat: DATA_SEARCHSONGS, criteria, arc4random() * 0xffffffff, theType, magic];
		default:
			break;
	}
	
	NSArray *userData = [NSArray arrayWithObjects:[NSNumber numberWithInt: CT_LISTSONG + type], criteria, nil];
	return (int)[self.httpClient connect: url withDelegate:self andPostData: data andUserData: userData];
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

- (NSMutableArray*) parseSongList: (GDataXMLDocument*) doc
{
	NSMutableArray* array = nil;
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
		if (array) {
			[array addObject: song];
		}
		else {
			array = [NSMutableArray arrayWithObject: song];
		}
		
		[song release];
		
	}
	
	return array;
}
	

- (void) connection: (HttpConnectionId)connection didFinishWithData: (NSData*) data andError: (NSError*) error andUserData: (id) userData {
	int type = [(NSNumber*)[userData objectAtIndex:0] intValue];
	NSString *criteria = [userData count] > 1 ? [userData objectAtIndex:1] : nil;
	
	if (error != nil)
	{
		NSLog(@"http, type:%d, err:%@", type, [error localizedDescription]);
		return;
	}
	
	NSString *string = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
	NSLog(@"http, done, %@", string);
	
	GDataXMLDocument *doc = [[[GDataXMLDocument alloc] initWithData:data options:0 error:nil] autorelease];
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
		
		[self listSongsByType:type withCriteria:criteria];	// retry to list songs
		return;
	}
	
	switch (type) {
		case CT_LISTSONG + SLT_GIVEN:
		case CT_LISTSONG + SLT_NEXT:
		{	
			NSArray *array = [self parseSongList:doc];

			if ([self.playList count] < PLAYLISTSIZE) {
				int addcount = PLAYLISTSIZE - [self.playList count];
				if (addcount > [array count]) {
					addcount = [array count];
				}
				[self.playList addObjectsFromArray: [array subarrayWithRange: NSMakeRange(0, addcount)]];
				[self.songs addObjectsFromArray: [array subarrayWithRange: NSMakeRange(addcount, [array count] - addcount)]];
				[self saveGivenIds];
			}
			else {
				[self.songs addObjectsFromArray: array];
			}

			[[NSNotificationCenter defaultCenter] postNotificationName:@"kSongDidLoad" object:nil];
			
			break;
		}
		case CT_LISTSONG + SLT_SEARCH:
		{
			self.searchResults = [self parseSongList:doc];
			
			[[NSNotificationCenter defaultCenter] postNotificationName:@"kSearchDidFinish" object:nil];
			break;
		}
		default:
			break;
	}

}


@end


