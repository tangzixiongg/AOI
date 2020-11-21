#include "view_manager.h"

inline bool is_in_view_area(int16_t center_x, int16_t center_y, int16_t view_x, int16_t view_y, int16_t view_size)
{
    return (view_x >= center_x - view_size && view_x <= center_x + view_size) &&
        (center_y >= center_y - view_size && view_y <= center_y + view_size);
}

void view::init(int32_t _nViewSize)
{
    if(_nViewSize <= 0 || _nViewSize >= 100)
    {
        return ;
    }
    m_nViewSize = _nViewSize;
    m_nCenterPointXZ = m_nViewSize * 2;
    m_vctCalculateViewsInfo.resize(4 * m_nViewSize + 1);

    for(int32_t i = 0; i < 4 * m_nViewSize ; ++i)
    {
        m_vctCalculateViewsInfo[i].resize(4 * m_nViewSize + 1);
    }

    for(int32_t x = -2 * m_nViewSize; x <= 2 * m_nViewSize ;++x)
    {
        for(int32_t z = -2 * m_nViewSize ; z <= 2 * m_nViewSize ; ++z)
        {
            cal_move_view_cell(x,z);
        }
    }
    m_bInit = true;
}

const aoi_calculate_result* view::get_aoi_view_result(int16_t x, int16_t y) const
{
    if(x < -2 * m_nViewSize || x > 2 * m_nViewSize || y < -2 * m_nViewSize || y > 2 * m_nViewSize)
    {
        return nullptr;
    }
    return &m_vctCalculateViewsInfo[x + m_nCenterPointXZ][y + m_nCenterPointXZ];
}

void view::cal_move_view_cell(int16_t x, int16_t y)
{
    int16_t view_size_in = m_nViewSize;   //进视野
    for(int16_t view_x = x - view_size_in ; view_x <= x + view_size_in ; ++view_x)
    {
        for(int16_t view_z = y - view_size_in ; view_z <= y + view_size_in ; ++view_z)
        {
            if(!is_in_view_area(0,0,view_x,view_z,view_size_in))
            {
                m_vctCalculateViewsInfo[x + m_nCenterPointXZ][y + m_nCenterPointXZ].appear_cells.emplace_back(glm::vec2(view_x,view_z));
            }
        }
    }

    int16_t view_size_out = m_nViewSize;  //出视野
    for(int16_t view_x = -view_size_out ; view_x <= view_size_out ; ++view_x)
    {
        for(int16_t view_z = -view_size_out ; view_z <= view_size_out ; ++view_z)
        {
            if(!is_in_view_area(x,y,view_x,view_z,view_size_out))
            {
                m_vctCalculateViewsInfo[x + m_nCenterPointXZ][y + m_nCenterPointXZ].appear_cells.emplace_back(glm::vec2(view_x,view_z));
            }
        }
    }
}

const aoi_calculate_result* view_manager::get_aoi_view_result(int32_t nViewSize, int16_t x, int16_t y)
{
    if(nViewSize > static_cast<int32_t>(m_calculate_views.size()) - 1)
    {
        return nullptr;
    }

    view & m_view = m_calculate_views[nViewSize];
    if(false == m_view.is_init())
    {
        m_view.init(nViewSize);
    }
    return m_view.get_aoi_view_result(x,y);

}

void view_manager::init_view_cell()
{

}

void view_manager::show()
{

}






