#pragma once
#include "Iobject.h"
#include "object_mgr.h"

class npc: public Iobject
{
public:
    npc(uint64_t qwObjId);
    virtual ~npc();

public:
    uint64_t get_uid() const override;
    ENUM_OBJ_TYPE get_type() const override;
    const QColor& get_color() const override;
    void set_color(QColor& color) override;

    bool is_role() const override;
    bool is_monster() const override;
    bool is_npc() const override;

    const position& cur_pos() const override;
    void set_position(const position& pos) override;
    void set_radius(uint32_t dwRadius) override;

    // vecFadeInObjUids 是进入本npc视野内的对象的uid的集合
    void fade_in(const std::vector<uint64_t>& vecFadeInObjUids) override;
    // vecFadeInObjUids 是离开本npc视野内的对象的uid的集合
    void fade_out(const std::vector<uint64_t>& vecFadeOutObjUids) override;

private:
    uint64_t m_qwUid;     // 惟一ID
    position  m_curPos;    // 当前位置
    uint32_t m_dwRadius;  // 半径
    ENUM_OBJ_TYPE m_eumObjType;
    QColor   m_color;
};


