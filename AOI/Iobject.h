#pragma onece

#include "aoi_interface.h"

class Iobject
{
public:
    Iobject(uint64_t dwUid, ENUM_OBJ_TYPE eumObjType, const QColor& color) {}
    virtual ~Iobject() {}
public:
    virtual uint64_t get_uid() const = 0;
    virtual ENUM_OBJ_TYPE get_type() const = 0;
    virtual const QColor& get_color() const = 0;
    virtual void set_color(QColor& color) = 0;

    virtual bool is_role() const = 0;
    virtual bool is_monster() const = 0;
    virtual bool is_npc() const = 0;

    virtual const position& cur_pos() const = 0;
    virtual void set_position(const position& pos) = 0;
    virtual void set_radius(uint32_t dwRadius) = 0;

    virtual void fade_in(const std::vector<uint64_t>& vecFadeInObjUids) = 0;
    virtual void fade_out(const std::vector<uint64_t>& vecFadeOutObjUids) = 0;

    bool can_see_target(uint64_t qwTargetUid) { return true; }
};

