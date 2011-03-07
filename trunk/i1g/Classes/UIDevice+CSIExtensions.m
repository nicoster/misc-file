//
//  UIDevice+CSIExtensions.m
//  Telephony
//

#import "UIDevice+CSIExtensions.h"
#include <sys/types.h>
#include <sys/sysctl.h>

#define UIDeviceCSIExtensionsIPhoneString			@"iPhone"
#define UIDeviceCSIExtensionsIPhone3GString			@"iPhone 3G"
#define UIDeviceCSIExtensionsIPhone3GSString		@"iPhone 3GS"
#define UIDeviceCSIExtensionsIPhoneSimulatorString	@"iPhone Simulator"
#define UIDeviceCSIExtensionsIPodTouchString		@"iPod Touch"
#define UIDeviceCSIExtensionsIPodTouch2GString		@"iPod Touch 2G"

@implementation UIDevice (CSIExtensions)

-(NSString *)modelDetailed
{
	// allocate memory
	size_t len = 0;
	sysctlbyname("hw.machine", NULL, &len, NULL, 0);
	char *machine = malloc(len);
	
	// read machine properties
	sysctlbyname("hw.machine", machine, &len, NULL, 0);
	
	// return the machine properties
	NSString *machineString = [NSString stringWithCString:machine encoding:NSUTF8StringEncoding];
	
	// free memory
	free(machine);
	
	// convert low-level machine name to user-readable name
	if ( [machineString isEqual:@"iPhone1,1"] )
	{
		machineString = UIDeviceCSIExtensionsIPhoneString;
	}
	else if ( [machineString isEqual:@"iPhone1,2"] )
	{
		machineString = UIDeviceCSIExtensionsIPhone3GString;
	}
	else if ( [machineString isEqual:@"iPhone2,1"] )
	{
		machineString = UIDeviceCSIExtensionsIPhone3GSString;
	}
	else if ( [machineString isEqual:@"i386"] )
	{
		machineString = UIDeviceCSIExtensionsIPhoneSimulatorString;
	}	
	else if ( [machineString isEqual:@"iPod1,1"] )
	{
		machineString = UIDeviceCSIExtensionsIPodTouchString;
	}
	else if ( [machineString isEqual:@"iPod2,1"] )
	{
		machineString = UIDeviceCSIExtensionsIPodTouch2GString;
	}	
	
	return machineString;
}

@end