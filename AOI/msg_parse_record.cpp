#include "msg_prase_record.h"


msg_hander_time_record::msg_hander_time_record(uint32_t id)
    :
    m_id(id)
{
    m_dwBeginTick = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

msg_hander_time_record::~msg_hander_time_record()
{
    uint64_t dwEnd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    uint32_t diffTime = dwEnd - m_dwBeginTick;
    MSGHANDERINSTANCE.add_msg_handle_record(m_id, diffTime);
}

msg_prase_manager::add_msg_handle_record(int32_t nId, int32_t nTime)
{
    auto iter = m_mapMsgHandleRecord.find(nId);
    if(iter == m_mapMsgHandleRecord.end())
    {
        msg_parase_time newTime(nId);
        newTime.add(newTime);
        m_mapMsgHandleRecord.insert(std::make_pair(mId,nTime));
    }
    else
    {
        iter.add(nTime);
        ++nCount;
    }

}
