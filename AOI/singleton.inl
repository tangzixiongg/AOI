#pragma once
#include "singleton.h"

template <typename ValueType, typename ThreadLock>
ThreadLock singleton<ValueType,ThreadLock>::s_lock;

template <typename ValueType, typename ThreadLock>
singleton<ValueType, ThreadLock>* singleton<ValueType,ThreadLock>::s_pInstance = nullptr;

template <typename ValueType, typename ThreadLock>
singleton<ValueType,ThreadLock>::singleton()
{
}

template <typename ValueType, typename ThreadLock>
ValueType* singleton<ValueType,ThreadLock>::instance()
{
    if (nullptr == s_pInstance)
    {
        std::unique_lock<ThreadLock> ul(s_lock);
        if (s_pInstance == nullptr)
        {
            void* pData = malloc((sizeof(singleton<ValueType,ThreadLock>)/sizeof(void*) + 1) * sizeof(void*));
            if (nullptr != pData)
            {
                s_pInstance = new (pData) singleton<ValueType,ThreadLock>();
            }
        }
    }
    if (nullptr != s_pInstance)
    {
        return &s_pInstance->m_oValue;
    }
    return nullptr;
}

template <typename ValueType, typename ThreadLock>
void singleton<ValueType,ThreadLock>::close()
{
    std::unique_lock<ThreadLock> ul(s_lock);
    if (nullptr != s_pInstance)
    {
        s_pInstance->~singleton();
        free(s_pInstance);
        s_pInstance = nullptr;
    }
}
