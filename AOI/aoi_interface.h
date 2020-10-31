#pragma once

#include "base_define.h"

class Iobject;

class aoi_interface
{

public:
    virtual ~aoi_interface() {}
    virtual bool init(const map_info& mapInfo) = 0;
    virtual void release() = 0;
    virtual bool enter(Iobject* pObj) = 0;
    virtual bool leave(Iobject* pObj) = 0;
    virtual void move_to(Iobject* pObj, position pos) = 0;
    virtual void get_near_obj_uids(Iobject* pObj, std::vector<uint64_t>& vecObjUids) = 0;

};

