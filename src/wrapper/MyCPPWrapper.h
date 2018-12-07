#ifndef __MYCPP_CLASS_H__
#define __MYCPP_CLASS_H__

class MyClassImpl;

class MyCPPWrapper {
public:
    MyCPPWrapper ( void );
    ~MyCPPWrapper( void );

    void init( void );
    int getAmbientLight( void );

private:
    MyClassImpl * _impl;
};

#endif
