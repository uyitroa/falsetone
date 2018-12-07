#include "MyCPPWrapper.h"
#include "MyObject-C-Interface.h"
#include <iostream>

MyCPPWrapper::MyCPPWrapper( void )
    : _impl ( NULL )
{   
}

void MyCPPWrapper::init( void )
{
    _impl = new MyClassImpl();
    _impl->init();
}

MyCPPWrapper::~MyCPPWrapper( void )
{
    if ( _impl ) { delete _impl; _impl = NULL; }
}

int MyCPPWrapper::getAmbientLight( void )
{
    return _impl->getAmbientLight( NULL );
}
