#pragma once

#include <mutex>

template<typename ValueType, typename ThreadLock = std::mutex>
class singleton
{
public:
    singleton();

public:
    static ValueType* instance();
    static void close();

private:
    ValueType m_oValue;

    static ThreadLock s_lock;
    static singleton<ValueType, ThreadLock>* s_pInstance;
};

#include "singleton.inl"
