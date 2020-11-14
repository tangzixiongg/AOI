#include "aoi_grid.h"
#include "Iobject.h"
#include <sstream>

grid_square::grid_square(int32_t nIndex): m_nIndex(nIndex)
{

}

grid_square::~grid_square()
{

}

void grid_square::insert_object(uint64_t qwObjUid)
{
    m_setObjectUid.emplace(qwObjUid);
}

void grid_square::remove_object(uint64_t qwObjUid)
{
    m_setObjectUid.erase(qwObjUid);
}

void grid_square::link_square(int32_t nNearIndex)
{
    m_vctNearSquareIndex.emplace_back(nNearIndex);
}

grid_square* aoi_grid_impl::get_grid_square(int32_t nIndex)
{
    if (nIndex >= 0 && nIndex < static_cast<int32_t>(m_vctSquare.size()))
    {
        return &m_vctSquare[nIndex];
    }
    return nullptr;
}

// 这里的 nX 和 nY 代表的是大格子的坐标
void aoi_grid_impl::link_to_square(int32_t nX, int32_t nY, grid_square &square)
{
    if (nX >= 0 && nY >= 0 && nX < m_mapInfo.m_nGridXcount && nY < m_mapInfo.m_nGridZcount)
    {
        square.link_square(nX + nY * m_mapInfo.m_nGridXcount);
    }
}

// 根据(x, y)坐标得到所在格子的索引，这里的(x, y)是角色的坐标，即小格子坐标
int32_t aoi_grid_impl::point_to_square_index(const position &pos)
{
    int32_t nX = (pos.m_nX - m_mapInfo.m_nLTX);
    int32_t nY = (pos.m_nY - m_mapInfo.m_nLTZ);

    int32_t nCX = nX / m_mapInfo.m_nSquareSize;
    int32_t nCY = nY / m_mapInfo.m_nSquareSize;
    if (nCX >= 0 && nCX < m_mapInfo.m_nGridXcount && nCY >= 0 && nCY <= m_mapInfo.m_nGridZcount)
    {
        return nCX + nCY * m_mapInfo.m_nGridXcount;
    }
    return -1;
}

// 得到 pObj 附近所有对象的uid
void aoi_grid_impl::get_grid_square_near_all_obj(grid_square *pGs, std::vector<uint64_t> &vctObjUid)
{
    if (nullptr == pGs)
    {
        return;
    }
    for (auto idx : pGs->get_near_squareIdx())
    {
        grid_square* pTmp = get_grid_square(idx);
        if (nullptr == pTmp)
        {
            continue;
        }
        const auto& gsObjs = pTmp->get_object_uids();
        vctObjUid.insert(vctObjUid.end(), gsObjs.begin(), gsObjs.end());
    }
}

aoi_grid_impl::aoi_grid_impl()
{

}

aoi_grid_impl::~aoi_grid_impl()
{

}

bool aoi_grid_impl::init(const map_info &mapInfo)
{
    m_mapInfo = mapInfo;

    for (int32_t i = 0; i < m_mapInfo.m_nGridXcount * m_mapInfo.m_nGridZcount; i++)
    {
        m_vctSquare.emplace_back(grid_square(i));
    }

    for (int32_t i = 0; i < m_mapInfo.m_nGridXcount * m_mapInfo.m_nGridZcount; i++)
    {
        grid_square& square = m_vctSquare[i];
        int32_t nX = i % m_mapInfo.m_nGridXcount;
        int32_t nY = i % m_mapInfo.m_nGridZcount;
        link_to_square(nX - 1, nY - 1, square);
        link_to_square(nX, nY - 1, square);
        link_to_square(nX + 1, nY - 1, square);

        link_to_square(nX - 1, nY, square);
        link_to_square(nX, nY, square);
        link_to_square(nX + 1, nY, square);

        link_to_square(nX - 1, nY + 1, square);
        link_to_square(nX, nY + 1, square);
        link_to_square(nX + 1, nY + 1, square);
    }
    return true;
}

// 计算两个数组的交集和差集,将两个数组相同项放在前面,以splitIdx作为分界,返回splitIdx
template<typename T>
int32_t calc_intersection_and_subtracation(std::vector<T>& vctFirst, std::vector<T>& vctSecond)
{
    int32_t nSplitIdx = 0;
    int32_t nLastUnmatchIdx = static_cast<int32_t>(vctFirst.size());
    while( nSplitIdx < nLastUnmatchIdx)
    {
        bool bFind = false;
        T firstVal = vctFirst[nSplitIdx];
        for (int32_t i = nSplitIdx, iMax = static_cast<int32_t>(vctSecond.size()); i < iMax; ++i)
        {
            if (vctSecond[i] == firstVal)
            {
                if (i != nSplitIdx)
                {
                    vctSecond[i] = vctSecond[nSplitIdx];
                    vctSecond[nSplitIdx] = firstVal;
                }
                ++nSplitIdx;
                bFind = true;
                break;
            }
        }

        if (!bFind)
        {
            vctFirst[nSplitIdx] = vctFirst[nLastUnmatchIdx - 1];
            vctFirst[nLastUnmatchIdx - 1] = firstVal;
            nLastUnmatchIdx--;
        }
    }
    return nSplitIdx;
}

// pObj 移动了，增加视野内新进的角色
bool aoi_grid_impl::enter(Iobject *pObj)
{
    if (nullptr == pObj)
    {
        return false;
    }

    // 得到所在格子
    grid_square* pGs = get_grid_square(point_to_square_index(pObj->cur_pos()));
    if (nullptr == pGs)
    {
        return false;
    }
    std::vector<uint64_t> vctFadeIn;
    get_grid_square_near_all_obj(pGs, vctFadeIn);
    pGs->insert_object(pObj->get_uid());
    pObj->fade_in(vctFadeIn);

    return true;
}

bool aoi_grid_impl::leave(Iobject *pObj)
{
    if (nullptr == pObj)
    {
        return false;
    }
    grid_square* pGs = get_grid_square(point_to_square_index(pObj->cur_pos()));
    if (nullptr == pGs)
    {
        return false;
    }
    std::vector<uint64_t> vctFadeOut;
    get_grid_square_near_all_obj(pGs, vctFadeOut);
    pGs->remove_object(pObj->get_uid());
    pObj->fade_out(vctFadeOut);
    return true;
}

// 角色移动位置，可能到一个新的格子也可能还处于原来的格子
void aoi_grid_impl::move_to(Iobject *pObj, position pos)
{
    //
    if (nullptr == pObj)
    {
        return;
    }

    grid_square *pOldGS = get_grid_square(point_to_square_index(pObj->cur_pos()));
    if (nullptr == pOldGS)
    {
        return;
    }

    grid_square *pNewGS = get_grid_square(point_to_square_index(pos));
    if (nullptr == pNewGS)
    {
        return;
    }

    if (pOldGS == pNewGS)
    {
        return;
    }

    std::vector<int32_t> vctFadeOldIdx = pOldGS->get_near_squareIdx();  //移动前附近格子的索引集合
    std::vector<int32_t> vctFadeNewIdx = pNewGS->get_near_squareIdx();  //移动后附近格子的索引集合
    int32_t nSplitIdx = calc_intersection_and_subtracation<int32_t>(vctFadeOldIdx, vctFadeNewIdx);

    std::vector<uint64_t> vctFadeInObjUid;  //新增对象的uid
    std::vector<uint64_t> vctFadeOutObjUid; //离开对象的uid
    for (int32_t i = nSplitIdx, iMax = static_cast<int32_t>(vctFadeNewIdx.size()); i < iMax; i++)
    {
        grid_square* pTmp = get_grid_square(vctFadeNewIdx[i]);
        if (nullptr != pTmp)
        {
            const auto& objs = pTmp->get_object_uids();
            vctFadeInObjUid.insert(vctFadeInObjUid.end(), objs.begin(), objs.end());
        }
    }

    for (int32_t i = nSplitIdx, iMax = static_cast<int32_t>(vctFadeOldIdx.size()); i < iMax; i++)
    {
        grid_square* pTmp = get_grid_square(vctFadeOldIdx[i]);
        if (nullptr != pTmp)
        {
            const auto& objs = pTmp->get_near_squareIdx();
            vctFadeOutObjUid.insert(vctFadeOutObjUid.end(), objs.begin(), objs.end());
        }
    }

    pOldGS->remove_object(pObj->get_uid());
    pNewGS->insert_object(pObj->get_uid());

    // 视野范围新增的对象集合
    pObj->fade_in(vctFadeInObjUid);

    // 视野范围减少的对象集合
    pObj->fade_out(vctFadeOutObjUid);
}

void aoi_grid_impl::get_near_obj_uids(Iobject *pObj, std::vector<uint64_t> &vecObjUids)
{
    if (nullptr == pObj)
    {
        return;
    }

    grid_square* pGs = get_grid_square(point_to_square_index(pObj->cur_pos()));
    if (nullptr == pGs)
    {
        return;
    }
    get_grid_square_near_all_obj(pGs, vecObjUids);
}

aoi_interface* make_aoi_grid()
{
    return new aoi_grid_impl();
}

















