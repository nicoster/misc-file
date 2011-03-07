//
//  UIDevice+CSIExtensions.h
//  Telephony
//

#import <UIKit/UIKit.h>

@interface UIDevice (CSIExtensions)

// returns the name of the device being used (iPhone 3G, iPod Touch 2G, etc)
-(NSString *)modelDetailed;

@end