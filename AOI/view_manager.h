#pragma once

#include <vector>
#include <array>
#include <stdint.h>
#include "singleton.h"

namespace glm {
    struct vec2
    {
        int16_t x;
        int16_t y;
        vec2(int16_t _x,int16_t _y)
        {
            x = _x;
            y = _y;
        }
    };
}

struct aoi_calculate_result
{
    std::vector<glm::vec2> appear_cells;
    std::vector<glm::vec2> disappear_cells;
};

constexpr uint16_t DIFF_IN_OUT = 1;

class view
{
public:
    void init(int32_t _nViewSize);
    bool is_init() const { return m_bInit;}
    const aoi_calculate_result* get_aoi_view_result(int16_t x, int16_t y) const;
private:
    void cal_move_view_cell(int16_t x, int16_t y);
private:
    int32_t m_nViewSize = 0;
    std::vector<std::vector<aoi_calculate_result>> m_vctCalculateViewsInfo;
    bool m_bInit = false;
    uint16_t m_nCenterPointXZ = 0;
};

class view_manager
{
public:
    view_manager() {}
    ~view_manager() {}

    void init_view_cell();
    const aoi_calculate_result* get_aoi_view_result(int32_t nViewSize, int16_t x, int16_t y);
    void show();
private:
     std::array<view, 26> m_calculate_views;
};

#define VIEW_CELL_MGR (*(singleton<view_manager>::instance()))
