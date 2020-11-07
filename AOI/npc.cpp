#include "npc.h"

npc::npc(uint64_t qwObjId): Iobject(qwObjId, ENUM_OBJ_TYPE::E_OBJ_TYPE_NPC, QColor(255, 255, 0))
{

}

npc::~npc()
{

}

uint64_t npc::get_uid() const
{
    return m_qwUid;
}
ENUM_OBJ_TYPE npc::get_type() const
{
    return m_eumObjType;
}
const QColor& npc::get_color() const
{
    return m_color;
}
void npc::set_color(QColor& color)
{
    m_color = color;
}

bool npc::is_role() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_ROLE;
}
bool npc::is_monster() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_MONSTER;
}
bool npc::is_npc() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_NPC;
}

const position& npc::cur_pos() const
{
    return m_curPos;
}
void npc::set_position(const position& pos)
{
    m_curPos = pos;
}
void npc::set_radius(uint32_t dwRadius)
{
    m_dwRadius = dwRadius;
}

// 如果进来的对象中有role则表示本npc进入了role的视野内，那么本npc要更改颜色
void npc::fade_in(const std::vector<uint64_t>& vecFadeInObjUids)
{
     if (is_role())
     {
         return;
     }
     for (auto uid : vecFadeInObjUids)
     {
         if (uid == get_uid())
         {
             continue;
         }
         Iobject* pObj = nullptr; // = 单例get_object(uid);
         if (nullptr != pObj && pObj->is_role())
         {
             //this->set_color();
             break;
         }
     }
}
void npc::fade_out(const std::vector<uint64_t>& vecFadeOutObjUids)
{
    if (is_role())
    {
        return;
    }
    for (auto uid : vecFadeOutObjUids)
    {
        if (uid == get_uid())
        {
            continue;
        }
        Iobject* pObj = nullptr; // = 单例get_object(uid);
        if (nullptr != pObj && pObj->is_role())
        {
            //this->set_color();
            break;
        }
    }
}
