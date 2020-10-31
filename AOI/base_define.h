#ifndef BASE_DEFINE_H
#define BASE_DEFINE_H

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

#define ROLE_COLOR (Qt::black)
#define NPC_COLOR (Qt::yellow)
#define MONSTER_COLOR (Qt::bule)
#define IN_VIEW_COLOR (Qt::red)


// 角色枚举
enum class ENUM_OBJ_TYPE
{
    E_OBJ_TYPE_ROLE = 1,    // 玩家
    E_OBJ_TYPE_MONSTER =2,  // 怪物
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



#endif // BASE_DEFINE_H
