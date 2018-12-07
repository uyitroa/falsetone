#import "MyObject-C-Interface.h"
#include <mach/mach.h>
#import <IOKit/IOKitLib.h>
#import <CoreFoundation/CoreFoundation.h>
static io_connect_t dataPort = 0;
@interface MyObject : NSObject
{
	int somevar;
}

- (int)  getAmbientLight:( void* ) aParameter;

@end
