#include "role.h"

role::role(uint64_t qwObjId): Iobject(qwObjId, ENUM_OBJ_TYPE::E_OBJ_TYPE_ROLE, QColor(0, 0, 0))
{
    m_eumObjType = ENUM_OBJ_TYPE::E_OBJ_TYPE_ROLE;
    m_color = QColor(0, 0, 0);
    m_qwUid = qwObjId;
    m_dwRadius = 0;
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


void role::fade_in(const std::vector<uint64_t>& vecFadeInObjUids)
{
     for (auto uid : vecFadeInObjUids)
     {
         if (uid == get_uid())
         {
             continue;
         }
         Iobject* pObj = OBJECTMGR.get_object(uid);
         if (nullptr != pObj)
         {
             QColor cl(255, 0, 0);
             pObj->set_color(cl);
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
        Iobject* pObj = OBJECTMGR.get_object(uid);
        if (nullptr != pObj)
        {
            if (pObj->is_npc())
            {
                QColor cl(0, 255, 0);
                pObj->set_color(cl);
            }
            else if (pObj->is_monster())
            {
                QColor cl(132, 112 ,255);
                pObj->set_color(cl);
            }
        }
    }
}
