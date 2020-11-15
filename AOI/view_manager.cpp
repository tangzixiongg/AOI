#include "view_manager.h"

void view::init(int32_t _nViewSize)
{

}

const aoi_calculate_result* view::get_aoi_view_result(int16_t x, int16_t y) const
{

}

void view::cal_move_view_cell(int16_t x, int16_t y)
{

}


void view_manager::init_view_cell()
{

}
const aoi_calculate_result* view_manager::get_aoi_view_result(int32_t nViewSize, int16_t x, int16_t y)
{

}
void view_manager::show()
{

}

inline bool is_in_view_area(int16_t center_x, int16_t center_y, int16_t view_x, int16_t view_y, int16_t view_size)
{
    return (view_x >= center_x - view_size && view_x <= center_x + view_size) &&
        (center_y >= center_y - view_size && view_y <= center_y + view_size);
}
