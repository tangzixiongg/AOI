#pragma once

#include <stdint.h>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <assert.h>
#include <list>
#include <algorithm>
#include <memory>
#include <qcolor.h>
#include <QColorDialog>

// 角色颜色
/*
QColor ROLE_COLOR(0, 0, 0);             // 黑色
QColor MONSTER_COLOR(255, 222, 173);    // 蓝色
QColor NPC_COLOR(255, 255, 0);          // 黄色
QColor IN_VIEW_COLOR(255, 0, 0);        // 红色
*/

/*
#define ROLE_COLOR (QColor(0, 0, 0))
#define MONSTER_COLOR (QColor(255, 222, 173))
#define NPC_COLOR (QColor(255, 255, 0))
#define IN_VIEW_COLOR (QColor(255, 0, 0))
*/

// 角色枚举
enum class ENUM_OBJ_TYPE
{
    E_OBJ_TYPE_ROLE = 1,    // 玩家
    E_OBJ_TYPE_MONSTER = 2,  // 怪物
    E_OBJ_TYPE_NPC = 3,     // npc
};

// 角色坐标点
class position
{
public:
    position(int32_t nX, int32_t nY): m_nX(nX), m_nY(nY) {}
    position(): m_nX(0), m_nY(0) {}
    bool operator==(const position& other)
    {
        return (m_nX == other.m_nX) && (m_nY == other.m_nY);
    }
private:
    int32_t m_nX;
    int32_t m_nY;
};

// 地图信息
class map_info
{
public:
    map_info(){}

private:

};



