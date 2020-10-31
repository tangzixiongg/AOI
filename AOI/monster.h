#pragma once

#include "Iobject.h"

class monster: public Iobject
{
public:
    monster(uint64_t qwObjId);
    virtual ~monster();
};


