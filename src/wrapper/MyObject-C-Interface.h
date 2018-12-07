#ifndef __MYOBJECT_C_INTERFACE_H__
#define __MYOBJECT_C_INTERFACE_H__

class MyClassImpl
{
public:
    MyClassImpl ( void );
    ~MyClassImpl( void );

    void init( void );
    int getAmbientLight( void* aParameter );

private:
    void * self;
};

#endif
