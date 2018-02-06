#ifndef LOCAL_H
#define LOCAL_H

#include "defines.h"

class Local
{
public:
    Local();
    ~Local();
    Local(char* name, MyPoint* point);
    MyPoint *point;
    char *name;
    static const int MAXIMUM_NAME_SIZE = 50;
};

#endif // LOCAL_H
