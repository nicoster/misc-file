//
//  NXHttpClient.m
//  iPhoneStreamingPlayer
//
//  Created by Nick Xiao on 2/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NXHttpClient.h"

@interface NXHttpClientData()


@property (nonatomic, retain, readwrite) NSMutableData* connectionData;
@property (nonatomic, retain, readwrite) NSURLConnection* connection;
@property (nonatomic, retain, readwrite) id userData;


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

@synthesize delegate, connectionData, connection, userData;

- (id) init {
	self = [super init];
	if (self == nil) return nil;
	
	self.connection = nil;
	self.connectionData = [[NSMutableData alloc] init];
	connectionResponse = nil;
	self.delegate = nil;
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
	self.delegate = nil;
	self.userData = nil;
	[super dealloc];
}

#pragma mark -
#pragma mark NSURLConnection Delegate Methods 

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    [connectionResponse release];
    connectionResponse = [response retain];
    [connectionData setLength:0];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [connectionData appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)aConnection {
	if ([self.delegate respondsToSelector:@selector(connection:didFinishWithData:andError:andUserData:)]) {
		[self.delegate connection: aConnection didFinishWithData: connectionData andError: nil andUserData: self.userData];
	}
		
	[[NXHttpClient sharedHttpClient] endConnection: aConnection];
}

- (void)connection:(NSURLConnection *)aConnection didFailWithError:(NSError *)error {
	if ([self.delegate respondsToSelector:@selector(connection:didFinishWithData:andError:andUserData:)]) {
		[self.delegate connection: aConnection didFinishWithData: connectionData andError: error andUserData: self.userData];
	}
	
	NSLog(@"http, connection failed. %@", [error localizedDescription]);
	
	[[NXHttpClient sharedHttpClient] endConnection: connection];
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


- (NSValue*) keyWithURLConnection: (NSURLConnection*) connection {
	return [NSValue valueWithNonretainedObject: connection];
}

- (id) init
{
//	NSAssert(self == nil, @"NXHttpClient has already been initialized.");
	self = [super init];
	if (self == nil) return nil;
	
	self.connections = [[[NSMutableDictionary alloc] initWithCapacity:1] autorelease];
	return self;
}

- (void) endConnection: (HttpConnectionId) connection
{
	NSLog(@"http, end:%d, retain:%d", connection, [connection retainCount]);
	[self.connections removeObjectForKey: [self keyWithURLConnection: connection]];
	NSLog(@"http, ~end:%d, retain:%d", connection, [connection retainCount]);
}

- (void) dealloc
{
	[super dealloc];
	self.connections = nil;
}


- (HttpConnectionId)connect: (NSString *)urlstring withDelegate: (id<NXHttpClientDelegate>) delegate andPostData: (NSString*) dataToPost andUserData: (id) userData {
	
	NSLog(@"http, url:%@", urlstring);
	NSURL *url = [NSURL URLWithString:urlstring];
	
	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
	[request setCachePolicy:NSURLRequestReloadIgnoringCacheData];
	[request setHTTPMethod:@"POST"];
//	[request setValue:@"application/xml; charset=utf-8" forHTTPHeaderField:@"Content-Type"];
	dataToPost = [dataToPost stringByAddingPercentEscapesUsingEncoding: NSASCIIStringEncoding];
	NSLog(@"http, %@", dataToPost);
	[request setHTTPBody:[dataToPost dataUsingEncoding:NSUTF8StringEncoding]];
						  
	NXHttpClientData* data = [[[NXHttpClientData alloc] init] autorelease];
//	NSLog(@"http, NXHttpClientData:%d retain:%d", data, [data retainCount]);
	
    NSURLConnection* connection = [[[NSURLConnection alloc] initWithRequest:request delegate:data] autorelease];
    if (connection) {
		NSLog(@"http, connections retain:%d, count:%d, conn:%d", [self.connections retainCount], [self.connections count], connection);
		
		data.connection = connection;
		data.delegate = delegate;
		data.userData = userData;
		NSValue *key = [self keyWithURLConnection: connection];
		[self.connections setObject: data forKey: key];
	}
	else {
		NSLog(@"http, failed:NSURLConnection initWithRequest:%@", url);
    }
	
	return connection;
}

- (bool)isConnectionValid: (HttpConnectionId) connection
{
	NSValue *key = [self keyWithURLConnection: connection];
	id data = [connections objectForKey:key];
	return data != nil;
}


@end
