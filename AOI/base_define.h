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

const constexpr int32_t CM_PIXEL_NUM = 16; //1厘米的像素数
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

    map_info(int32_t _nWidth,int32_t _nHeight,int32_t _nSquareSize, int32_t _nViewSize)
    {
        nWidth = _nWidth;
        nHeight = _nHeight;
        nSquareSize = _nSquareSize;
        nViewSize = _nViewSize;

        nScreenWidthPixel = nWidth * CM_PIXEL_NUM;
        nScreenHeightPiexl = nHeight * CM_PIXEL_NUM;
        nGridSquarePixelNum = nSquareSize * CM_PIXEL_NUM;

        nGridXcount = nWidth / nSquareSize + 1;
        nGridZcount = nHeight / nSquareSize + 1;
    }


private:
    int32_t nNPCnums = 20; //随机生成的NPC个数
    int32_t nMonsternums = 200; //随机生成的怪物的个数
    int32_t nLTX = 0;   //地图左上角的X坐标
    int32_t nLTZ = 0;   //地图左上角的Y坐标

    int32_t nWidth = 100; //地图的宽度
    int32_t nHeight = 50; //地图的高度

    int32_t nSquareSize = 0;  //每个格子宽
    int32_t nViewSize = 1;   //视野半径格子数

    int32_t nScreenWidthPixel = 0; //屏幕的宽度的像素数
    int32_t nScreenHeightPiexl = 0;  //屏幕的高度像素数

    int32_t nGridSquarePixelNum = 0;   //每个格子的像素数
    int32_t nGridXcount = 0;   //X轴的格子数
    int32_t nGridZcount = 0;   //z轴格子数

    bool bMonsterMove = false;  //怪物是否移动
    bool bCheckViewObject = false; //是否检测玩家视野内的对象

};



