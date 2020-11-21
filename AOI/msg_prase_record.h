#pragma once

#include "base_define.h"
#include <windows.h>
#include <chrono>
#include "singleton.h"

struct msg_parase_time
{
    int32_t m_nId;
    int32_t m_nMaxTime;  //最大时间
    int32_t m_nMinTime;     //最小时间
    int32_t m_nAverageTime;  //平均时间
    int32_t m_nTotalTime;  //总时间

    int32_t m_nTimes;

    msg_parase_time(uint32_t _dwiId)
    {
        m_nId = _dwiId;
        m_nMaxTime = 0;
        m_nMinTime = -1;
        m_nAverageTime = 0;
        m_nTotalTime = 0;
        m_nTimes = 0;
    }

    inline void add(int32_t _nTime)
    {
        this->m_nTotalTime += _nTime;
        this->m_nTimes++;
        if(m_nMaxTime < _nTime)
            this->m_nMaxTime = _nTime;
        if(m_nMinTime > _nTime)
            this->m_nMinTime = _nTime;

        if(this->m_nTimes > 12)
        {
            this->m_nAverageTime = (this->m_nTotalTime - this->m_nMaxTime - this->m_nMinTime ) / (this->m_nTimes-2);
        }
        else
        {
            this->m_nAverageTime = this->m_nTotalTime / this->m_nTimes;
        }
    }
};

typedef std::unordered_map<int32_t,msg_parase_time> MSGHANDLERECORE_MAP;

class msg_prase_manager
{
public:
    void add_msg_handle_record(int32_t nId,int32_t nTime);
private:
    struct TimeRecordCmpare
    {
        bool operator() (const msg_parase_time & left , const msg_parase_time & right)
        {
            if(left.m_nAverageTime > right.m_nAverageTime)
            {
                return true;
            }
            else if (left.m_nAverageTime < right.m_nAverageTime)
            {
                return false;
            }
            if(left.m_nMaxTime > left.m_nMaxTime)
            {
                return true;
            }
            return false;
        }
    };
    MSGHANDLERECORE_MAP m_mapMsgHandleRecord;
    int32_t nCount;
};

#define MSGHANDERINSTANCE (*(singleton<msg_prase_manager>::instance()))

class msg_hander_time_record
{
private:
    uint64_t		m_dwBeginTick;
    uint32_t		m_id;
public:
    msg_hander_time_record(uint32_t id);
    ~msg_hander_time_record();
};
