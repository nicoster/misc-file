//
//  NXHttpClient.h
//
//  Created by Nick Xiao on 2/21/11.
//  Copyright 2011 Cisco CSG. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef int HttpConnectionId;

@protocol NXHttpClientDelegate <NSObject>
- (void) connection: (HttpConnectionId)connection didFinishWithData: (NSData*) data andError: (NSError*) error andUserData: (id) userData; 
@end


@interface NXHttpClientData : NSObject
{
	NSDictionary *parameters;
	HttpConnectionId hid;
    NSURLConnection *connection;
    NSURLResponse *connectionResponse;
    NSMutableData *connectionData;
//	id<NXHttpClientDelegate> delegate;
//	id userData;
}

//@property (nonatomic, retain) id<NXHttpClientDelegate> delegate;

@end

@interface NXHttpClient : NSObject {
	NSMutableDictionary* connections;
}

+ (NXHttpClient*) sharedHttpClient;
- (HttpConnectionId) connect: (NSString*) url withDelegate: (id<NXHttpClientDelegate>) delegate andPostData: (NSString*) data andUserData: (id) userData;
- (NSString*) dataToPostForConnection: (HttpConnectionId) hid;
- (bool)setDataToPost: (NSString*) data forConnection: (HttpConnectionId) hid;
- (HttpConnectionId)connectWithParams: (NSDictionary*) params andHttpConnectionId: (HttpConnectionId) hid;

@end
