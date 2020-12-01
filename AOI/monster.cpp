#include "monster.h"

monster::monster(uint64_t qwObjId): Iobject(qwObjId, ENUM_OBJ_TYPE::E_OBJ_TYPE_MONSTER, QColor(132, 112 ,255))
{
    m_eumObjType = ENUM_OBJ_TYPE::E_OBJ_TYPE_MONSTER;
    m_color = QColor(132, 112 ,255);
    m_qwUid = qwObjId;
    m_dwRadius = 0;
}

monster::~monster()
{

}

uint64_t monster::get_uid() const
{
    return m_qwUid;
}
ENUM_OBJ_TYPE monster::get_type() const
{
    return m_eumObjType;
}
const QColor& monster::get_color() const
{
    return m_color;
}
void monster::set_color(QColor& color)
{
    m_color = color;
}

bool monster::is_role() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_ROLE;
}
bool monster::is_monster() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_MONSTER;
}
bool monster::is_npc() const
{
    return m_eumObjType == ENUM_OBJ_TYPE::E_OBJ_TYPE_NPC;
}

const position& monster::cur_pos() const
{
    return m_curPos;
}
void monster::set_position(const position& pos)
{
    m_curPos = pos;
}
void monster::set_radius(uint32_t dwRadius)
{
    m_dwRadius = dwRadius;
}

// 如果进来的对象中有role则表示本monster进入了role的视野内，那么本monster要更改颜色
void monster::fade_in(const std::vector<uint64_t>& vecFadeInObjUids)
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
         Iobject* pObj = OBJECTMGR.get_object(uid);
         if (nullptr != pObj && pObj->is_role())
         {
             QColor cl(255, 0, 0);
             this->set_color(cl);
             break;
         }
     }
}
void monster::fade_out(const std::vector<uint64_t>& vecFadeOutObjUids)
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
        Iobject* pObj = OBJECTMGR.get_object(uid);
        if (nullptr != pObj && pObj->is_role())
        {
            QColor cl(132, 112 ,255);
            this->set_color(cl);
            break;
        }
    }
}
