#ifndef OBJECT_MGR_H
#define OBJECT_MGR_H

#include "base_define.h"
#include "singleton.h"

class Iobject;

class object_mgr
{
public:
    object_mgr();
    ~object_mgr();
public:
    static uint64_t get_unique_id();
    void add_object(Iobject* pObj);
    void remove_object(uint64_t qwUid);
    Iobject* get_object(uint64_t qwUid);
    void iter_all_object(std::function<bool(Iobject*)> func);

private:
    std::unordered_map<uint64_t, Iobject*> m_umapObject;
    static uint64_t m_uniqueId;
};

#define OBJECTMGR (*(singleton<object_mgr>::instance()))

#endif // OBJECT_MGR_H
