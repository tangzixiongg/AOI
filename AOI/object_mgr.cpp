#include "object_mgr.h"
#include "Iobject.h"

uint64_t object_mgr::m_uniqueId = 10000;

uint64_t object_mgr::get_unique_id()
{
    return m_uniqueId++;
}

object_mgr::object_mgr()
{

}

object_mgr::~object_mgr()
{
    for (auto iter : m_umapObject)
    {
        delete iter.second;
        iter.second = nullptr;
    }
    m_umapObject.clear();
}

void object_mgr::add_object(Iobject *pObj)
{
    if (nullptr == pObj)
    {
        return;
    }
    m_umapObject.emplace(pObj->get_uid(), pObj);
}

void object_mgr::remove_object(uint64_t qwUid)
{
    m_umapObject.erase(qwUid);
}

Iobject* object_mgr::get_object(uint64_t qwUid)
{
    auto iter = m_umapObject.find(qwUid);
    if (iter != m_umapObject.end())
    {
        return iter->second;
    }
    return nullptr;
}

void object_mgr::iter_all_object(std::function<bool (Iobject *)> func)
{
    for (auto& iter : m_umapObject)
    {
        if (!func(iter.second))
        {
            return;
        }
    }
}



