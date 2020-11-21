#ifndef AOI_GRID_H
#define AOI_GRID_H

#include <vector>
#include <set>
#include "aoi_interface.h"

// 打格子
class grid_square
{
public:
    grid_square(int32_t nIndex);
    ~grid_square();

public:
    void insert_object(uint64_t qwObjUid);
    void remove_object(uint64_t qwObjUid);

    void link_square(int32_t nNearIndex);

    const std::set<uint64_t>& get_object_uids() const { return m_setObjectUid; }
    const std::vector<int32_t>& get_near_squareIdx() const { return m_vctNearSquareIndex; }

private:
    int32_t m_nIndex = 0;
    std::vector<int32_t> m_vctNearSquareIndex;  // 附近格子的索引
    std::set<uint64_t> m_setObjectUid;  // 该格子能看到的所有对象的id
};


class aoi_grid_impl: public aoi_interface
{
public:
    aoi_grid_impl();
    virtual ~aoi_grid_impl();

protected:
    grid_square* get_grid_square(int32_t nIndex);
    void link_to_square(int32_t nX, int32_t nY, grid_square& square);
    int32_t point_to_square_index(const position& pos);
    void get_grid_square_near_all_obj(grid_square* pGs, std::vector<uint64_t>& vctObjUid);

public:
    bool init(const map_info& mapInfo) override;
    bool enter(Iobject* pObj) override;
    bool leave(Iobject* pObj) override;
    void move_to(Iobject* pObj, position pos) override;
    void get_near_obj_uids(Iobject* pObj, std::vector<uint64_t>& vecObjUids) override;
private:
    std::vector<grid_square> m_vctSquare;   // 存地图上所有的格子
    map_info m_mapInfo;
};

aoi_interface* make_aoi_grid();

#endif // AOI_GRID_H
