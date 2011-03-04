//
//  NXHttpClient.m
//  iPhoneStreamingPlayer
//
//  Created by Nick Xiao on 2/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NXHttpClient.h"


NSString * const kNXHttpClientURL = @"kNXHttpClientURL";
NSString * const kNXHttpClientDelegate = @"kNXHttpClientDelegate";
NSString * const kNXHttpClientData = @"kNXHttpClientData";
NSString * const kNXHttpClientUserData = @"kNXHttpClientUserData";
NSString * const kNXHttpClientConnection = @"kNXHttpClientConnection";
NSString * const kNXHttpClientContentType = @"kNXHttpClientContentType";



@interface NXHttpClientData()


@property (nonatomic, retain, readwrite) NSMutableData* connectionData;
@property (nonatomic, retain, readwrite) NSURLConnection* connection;
@property (nonatomic, retain, readwrite) NSDictionary* params;
@property (nonatomic, assign) HttpConnectionId hid;



/* NSURLConnection Delegate Methods */
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
@end

@interface NXHttpClient()

- (bool)isConnectionValid: (HttpConnectionId) connection;
- (void)endConnection: (HttpConnectionId) connection;

@property (nonatomic, retain, readwrite) NSMutableDictionary* connections;
@end

@implementation NXHttpClientData

@synthesize connectionData, connection, hid, params = parameters;

- (id) init {
	self = [super init];
	if (self == nil) return nil;
	
	self.connection = nil;
	self.connectionData = [[NSMutableData alloc] init];
	connectionResponse = nil;
	self.params = nil;
	return self;
}

- (id) initWithConnection: (NSURLConnection*) aConnection
{
	self = [self init];
	if (self == nil) return nil;
	
	self.connection = aConnection;
	return self;
}

- (void) dealloc
{
	self.connectionData = nil;
	self.connection = nil;
	[connectionResponse release];
	connectionResponse = nil;
	self.params = nil;
	self.hid = 0;
	[super dealloc];
}

#pragma mark -
#pragma mark NSURLConnection Delegate Methods 

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
	[response retain];
    [connectionResponse release];
    connectionResponse = response;
    [connectionData setLength:0];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [connectionData appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)aConnection {
	id<NXHttpClientDelegate> theDelegate = (id<NXHttpClientDelegate>)[self.params objectForKey:kNXHttpClientDelegate];
	id theUserData = [self.params objectForKey:kNXHttpClientUserData];
	
	if ([theDelegate respondsToSelector:@selector(connection:didFinishWithData:andError:andUserData:)]) {

		[theDelegate connection: self.hid didFinishWithData: connectionData andError: nil andUserData: theUserData];
	}
		
	[[NXHttpClient sharedHttpClient] endConnection: self.hid];
}

- (void)connection:(NSURLConnection *)aConnection didFailWithError:(NSError *)error {
	id<NXHttpClientDelegate> theDelegate = (id<NXHttpClientDelegate>)[self.params objectForKey:kNXHttpClientDelegate];
	id theUserData = [self.params objectForKey:kNXHttpClientUserData];
	
	if ([theDelegate respondsToSelector:@selector(connection:didFinishWithData:andError:andUserData:)]) {
		[theDelegate connection: self.hid didFinishWithData: connectionData andError: error andUserData: theUserData];
	}
	
	NSLog(@"http, connection failed. %@", [error localizedDescription]);
	
	[[NXHttpClient sharedHttpClient] endConnection: self.hid];
}

- (NSCachedURLResponse *)connection:(NSURLConnection *)connection willCacheResponse:(NSCachedURLResponse *)cachedResponse {
    return nil;     // Never cache
}

@end


@implementation NXHttpClient

@synthesize connections;

+ (NXHttpClient*) sharedHttpClient
{
	static NXHttpClient* hc = nil;
	
	@synchronized(hc)
	{
		if (hc == nil)
		{
			hc = [[NXHttpClient alloc] init];
		}
	}
	
	return hc;
}

- (HttpConnectionId) nextHttpConnectionId {
	@synchronized(self)
	{
		static int i = 1;
		return i ++;
	}
}

- (NXHttpClientData*) httpDataByConnection: (NSURLConnection*) connection
{
	NSEnumerator *e = [connections objectEnumerator];
	NXHttpClientData* data = nil;
	
	while (data = [e nextObject]) {
		if (data.connection == connection) {
			return data;
		}
	}
	return nil;
}


- (NSValue*) keyWithHttpConnectionId: (HttpConnectionId) anId {
	return [NSNumber numberWithInt: anId];
}

- (id) init
{
	self = [super init];
	if (self == nil) return nil;
	
	self.connections = [[[NSMutableDictionary alloc] initWithCapacity:1] autorelease];
	return self;
}

- (void) endConnection: (HttpConnectionId) connection
{
//	NSLog(@"http, end:%d, retain:%d", connection, [connection retainCount]);
	NXHttpClientData *data = [self httpDataByConnection: (NSURLConnection*)connection];
	[self.connections removeObjectForKey: [self keyWithHttpConnectionId: data.hid]];
//	NSLog(@"http, ~end:%d, retain:%d", connection, [connection retainCount]);
}

- (void) dealloc
{
	self.connections = nil;
	[super dealloc];
}

- (NSString*) dataToPostForConnection: (HttpConnectionId) hid
{
	NSValue *key = [self keyWithHttpConnectionId: hid];
	NXHttpClientData *internalData = [connections objectForKey:key];
	if (internalData == nil) {
		return nil;
	}
	
	return [internalData.params valueForKey:@"kNXHttpClientData"];
}

- (bool)setDataToPost: (NSString*) data forConnection: (HttpConnectionId) hid
{
	NSValue *key = [self keyWithHttpConnectionId: hid];
	NXHttpClientData *internalData = [connections objectForKey:key];
	if (internalData == nil) {
		return NO;
	}
	
	[internalData.params setValue:data forKey:@"kNXHttpClientData"];
	return YES;
}

- (HttpConnectionId)connectWithParams: (NSDictionary*) params andHttpConnectionId: (HttpConnectionId) hid
{
	if (params == nil) {
		NSValue *key = [self keyWithHttpConnectionId: hid];
		NXHttpClientData *internalData = [connections objectForKey:key];
		if (internalData == nil) {
			return 0;
		}
		
		params = internalData.params;
	}
	
	NSURL *url = [NSURL URLWithString:[params objectForKey:kNXHttpClientURL]];
	
	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
	[request setCachePolicy:NSURLRequestReloadIgnoringCacheData];
	[request setHTTPMethod:@"POST"];
	//[request setValue:@"application/xml; charset=utf-8" forHTTPHeaderField:@"Content-Type"];
	NSString *dataToPost = [[params objectForKey:kNXHttpClientData] stringByAddingPercentEscapesUsingEncoding: NSASCIIStringEncoding];
	NSLog(@"http, %@", dataToPost);
	[request setHTTPBody:[dataToPost dataUsingEncoding:NSUTF8StringEncoding]];
	
	NXHttpClientData* data = [[[NXHttpClientData alloc] init] autorelease];
	//	NSLog(@"http, NXHttpClientData:%d retain:%d", data, [data retainCount]);
	
    NSURLConnection* connection = [[[NSURLConnection alloc] initWithRequest:request delegate:data] autorelease];
    if (connection) {
		NSLog(@"http, connections retain:%d, count:%d, conn:%d", [self.connections retainCount], [self.connections count], connection);
		
		hid = [self nextHttpConnectionId];
		data.params = params;
		data.connection = connection;
		data.hid = hid;
		[self.connections setObject: data forKey: [self keyWithHttpConnectionId: hid]];
	}
	else {
		NSLog(@"http, failed:NSURLConnection initWithRequest:%@", url);
    }
	
	return hid;
	
}

- (HttpConnectionId)connect: (NSString *)urlstring withDelegate: (id<NXHttpClientDelegate>) delegate andPostData: (NSString*) dataToPost andUserData: (id) userData {
	NSMutableDictionary *dict = [NSMutableDictionary dictionaryWithObjectsAndKeys:
								 urlstring, kNXHttpClientURL,
								 delegate, kNXHttpClientDelegate,
								 dataToPost, kNXHttpClientData,
								 userData, kNXHttpClientUserData, nil];
	
	return [self connectWithParams: dict andHttpConnectionId: 0];
}

- (bool)isConnectionValid: (HttpConnectionId) connection
{
	NSValue *key = [self keyWithHttpConnectionId: connection];
	id data = [connections objectForKey:key];
	return data != nil;
}


@end
