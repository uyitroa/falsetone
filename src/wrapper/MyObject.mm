#import "MyObject.h"

@implementation MyObject

MyClassImpl::MyClassImpl( void )
    : self( NULL )
{   
    kern_return_t kr;
    io_service_t serviceObject;

    serviceObject = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("AppleLMUController"));
    kr = IOServiceOpen(serviceObject, mach_task_self(), 0, &dataPort);
    IOObjectRelease(serviceObject);
}

MyClassImpl::~MyClassImpl( void )
{
    [(id)self dealloc];
}

void MyClassImpl::init( void )
{    
    self = [[MyObject alloc] init];
}

int MyClassImpl::getAmbientLight( void* aParameter)
{
    return [(id)self getAmbientLight:aParameter];
}
- (int) getAmbientLight:( void* ) aParameter
{
    kern_return_t kr;
    uint32_t outputs = 2;
    uint64_t values[outputs];

    kr = IOConnectCallMethod(dataPort, 0, nil, 0, nil, 0, values, &outputs, nil, 0);
    if (kr == KERN_SUCCESS) {
        return values[0];
    }
    return 0;
}
@end
