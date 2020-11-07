#include "role.h"

role::role(uint64_t qwObjId): Iobject(qwObjId, ENUM_OBJ_TYPE::E_OBJ_TYPE_ROLE, QColor(0, 0, 0))
{

}

role::~role()
{

}

uint64_t role::get_uid() const
{
    return m_qwUid;
}
ENUM_OBJ_TYPE role::get_type() const
{
    return m_eumObjType;
}
const QColor& role::get_color() const
{
    return m_color;
}
void role::set_color(QColor& color)
{
    m_color = color;
}

bool role::is_role() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_ROLE;
}
bool role::is_monster() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_MONSTER;
}
bool role::is_npc() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_NPC;
}

const position& role::cur_pos() const
{
    return m_curPos;
}
void role::set_position(const position& pos)
{
    m_curPos = pos;
}
void role::set_radius(uint32_t dwRadius)
{
    m_dwRadius = dwRadius;
}

// 如果进来的对象中有role则表示本npc进入了role的视野内，那么本npc要更改颜色
void role::fade_in(const std::vector<uint64_t>& vecFadeInObjUids)
{
     for (auto uid : vecFadeInObjUids)
     {
         if (uid == get_uid())
         {
             continue;
         }
         Iobject* pObj = nullptr;   // 单例
         if (nullptr != pObj)
         {
             //pObj->set_color(uid);
         }
     }
}
void role::fade_out(const std::vector<uint64_t>& vecFadeOutObjUids)
{
    for (auto uid : vecFadeOutObjUids)
    {
        if (uid == get_uid())
        {
            continue;
        }
        Iobject* pObj = nullptr;   // 单例
        if (nullptr != pObj)
        {
            if (pObj->is_npc())
            {
                //pObj->set_color();
            }
            else if (pObj->is_monster())
            {
                //pObj->set_color();
            }
        }
    }
}
