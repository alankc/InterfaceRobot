#include "local.h"

Local::Local()
{
    name = new char[MAXIMUM_NAME_SIZE];
}

Local::~Local()
{
    if (point != NULL)
        delete(point);
    if (name != NULL)
        delete(name);
}

Local::Local(char* name, MyPoint* point)
{
    this->name = name;
    this->point = point;
}

