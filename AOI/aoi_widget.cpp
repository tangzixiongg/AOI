#include "aoi_widget.h"

#include <iostream>
#include <QPainter>
#include <QKeyEvent>

#include "role.h"
#include "npc.h"
#include "monster.h"
#include "object_mgr.h"
#include "Iobject.h"
#include "msg_prase_record.h"

role * pRole = nullptr;

static constexpr int32_t TIME_INTERVAL = 200;

aoi_widget::aoi_widget(std::shared_ptr<aoi_interface> pAoi,const map_info& stMapInfo)
    :QWidget(nullptr),
      m_pAoi(pAoi),
      m_stMapInfo(stMapInfo)
{
    //设置窗口的大小
    bg_ = QPixmap(m_stMapInfo.m_nScreenWidthPixel, m_stMapInfo.m_nScreenHeightPiexl);
    QWidget::setFixedSize(bg_.size());

    //背景绘制
    bg_.fill(QColor(250,250,250));
    QPainter painter(&bg_);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);

    for(int32_t i = 0;i < m_stMapInfo.m_nWidth;i++)
    {
        painter.drawLine(i * CM_PIXEL_NUM, 0, i * CM_PIXEL_NUM,m_stMapInfo.m_nScreenHeightPiexl);
    }

    for(int32_t j = 0;j < m_stMapInfo.m_nHeight;j++)
    {
        painter.drawLine(0,j * CM_PIXEL_NUM,m_stMapInfo.m_nScreenWidthPixel,j * CM_PIXEL_NUM);
    }

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(55,215,255));

    for (int32_t i = 0; i <= m_stMapInfo.m_nGridXcount; ++i)
    {
        for (int32_t j = 0; j <= m_stMapInfo.m_nGridZcount; ++j)
        {
            int32_t nPosX = i * m_stMapInfo.m_nGridSquarePixelNum;
            int32_t nPosZ = j * m_stMapInfo.m_nGridSquarePixelNum;
            int32_t nRectW = m_stMapInfo.m_nGridSquarePixelNum;
            int32_t nRectH = m_stMapInfo.m_nGridSquarePixelNum;
            if ((nPosX + nRectW) > m_stMapInfo.m_nScreenWidthPixel)
            {
                nRectW = m_stMapInfo.m_nScreenWidthPixel - nPosX - 1;
            }
            if ((nPosZ + nRectH) > m_stMapInfo.m_nScreenHeightPiexl)
            {
                nRectH = m_stMapInfo.m_nScreenHeightPiexl - nPosZ - 1;
            }
            if (nRectW > 0 && nRectH > 0)
            {
                painter.drawRect(nPosX, nPosZ, nRectW, nRectH);
            }
        }
    }

    //srand(static_cast<unsigned int>(time(nullptr)));

    //生成地图上的对象
    //生成玩家
    srand(static_cast<unsigned int>(time(nullptr)));
    pRole = new role(OBJECTMGR.get_unique_id());

    OBJECTMGR.add_object(pRole);
    pRole->set_position(position(rand() % m_stMapInfo.m_nWidth, rand() % m_stMapInfo.m_nHeight));
    m_pAoi->enter(pRole);

    //生成NPC
    int32_t nNpcNum = m_stMapInfo.m_nNPCnums;
    for(int32_t i = 0; i < nNpcNum ; ++ i)
    {
        npc * pNpc = new npc(OBJECTMGR.get_unique_id());
        OBJECTMGR.add_object(pNpc);
        pNpc->set_position(position(rand() % m_stMapInfo.m_nWidth, rand() % m_stMapInfo.m_nHeight));
        m_pAoi->enter(pNpc);
    }

    //生成怪物
    int32_t nMonsterNun = m_stMapInfo.m_nMonsternums;
    for(int32_t i = 0; i < nMonsterNun ; ++i)
    {
        monster * pMonster = new monster(OBJECTMGR.get_unique_id());
        OBJECTMGR.add_object(pMonster);
        pMonster->set_position(position(rand() % m_stMapInfo.m_nWidth, rand() % m_stMapInfo.m_nHeight));
        m_pAoi->enter(pMonster);
    }

    //启动定时器
    QTimer * gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    gameTimer->start(TIME_INTERVAL);

    this->paintEvent(nullptr);
    //this->keyPressEvent(nullptr);
}

aoi_widget::~aoi_widget()
{

}

void aoi_widget::paintEvent(QPaintEvent *)
{
    //重载paintEvent函数绘制
    QPixmap canvas = bg_;
    OBJECTMGR.iter_all_object([this,&canvas](Iobject * pObj) -> bool {
        if(pObj->is_role())
        {
            this->draw_player(pObj->cur_pos(),pObj->get_color(),canvas);
            return true;
        }

        else if(pObj->is_npc())
        {
            this->draw_npc(pObj->cur_pos(),pObj->get_color(),canvas);
            return true;
        }
        else if(pObj->is_monster())
        {
            this->draw_monster(pObj->cur_pos(),pObj->get_color(),canvas);
            return true;
        }
        return true;
    });

    QPainter painter(this);
    painter.drawPixmap(0,0,canvas);
}

void aoi_widget::keyPressEvent(QKeyEvent *event)
{
    if (nullptr == pRole)
    {
        return;
    }
    position curPos = pRole->cur_pos();
    switch (event->key())
    {
    case Qt::Key_Up:
    {
        curPos.m_nY--;
        break;
    }
    case Qt::Key_Down:
    {
        curPos.m_nY++;
        break;
    }
    case Qt::Key_Left:
    {
        curPos.m_nX--;
        break;
    }
    case Qt::Key_Right:
    {
        curPos.m_nX++;
        break;
    }
    default:
        break;
    }

    if (curPos.m_nX < 0)
        curPos.m_nX = 0;
    if (curPos.m_nX >= m_stMapInfo.m_nWidth)
        curPos.m_nX--;
    if (curPos.m_nY < 0)
        curPos.m_nY = 0;
    if (curPos.m_nY >= m_stMapInfo.m_nHeight)
        curPos.m_nY--;

    m_pAoi->move_to(pRole, curPos);
    pRole->set_position(curPos);
}

void aoi_widget::draw_player(const position &pos, const QColor &qc ,QPixmap &canvas)
{
    QPainter painter(&canvas); //定义绘制基类
    painter.setBrush(qc); //定义用于填充形状的颜色和图案

    //绘制矩形
    painter.drawRect(pos.m_nX * CM_PIXEL_NUM,pos.m_nY * CM_PIXEL_NUM ,CM_PIXEL_NUM,CM_PIXEL_NUM);

    int32_t nGridx = pos.m_nX / m_stMapInfo.m_nSquareSize;
    int32_t nGridy = pos.m_nY / m_stMapInfo.m_nSquareSize;

    int32_t nLTPosX = nGridx - m_stMapInfo.m_nViewSize;
    int32_t nLTPosY = nGridy - m_stMapInfo.m_nViewSize;
    int32_t nRBPosX = nGridx + m_stMapInfo.m_nViewSize;
    int32_t nRBPosY = nGridy + m_stMapInfo.m_nViewSize;

    if(nLTPosX < 0)
        nLTPosX = 0;
    if(nLTPosY < 0)
        nLTPosY = 0;
    if(nRBPosX > m_stMapInfo.m_nGridXcount)
        nRBPosX = m_stMapInfo.m_nGridXcount;
    if(nRBPosY > m_stMapInfo.m_nGridZcount)
        nRBPosY = m_stMapInfo.m_nGridZcount;

    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::red);

    for(int32_t i = nLTPosX ; i <= nRBPosX ; ++i)
    {
        for (int32_t j = nLTPosY ; j <= nRBPosY ; ++j)
        {
            //绘制玩家的矩形，并填充红色
            painter.drawRect(i * m_stMapInfo.m_nGridSquarePixelNum, j * m_stMapInfo.m_nGridSquarePixelNum,m_stMapInfo.m_nGridSquarePixelNum,m_stMapInfo.m_nGridSquarePixelNum);
        }
    }
}

void aoi_widget::draw_npc(const position &pos, const QColor &qc, QPixmap &canvas)
{
    QPainter painter(&canvas);
    painter.setBrush(qc); //定义用于填充形状的颜色和图案
    painter.drawRect(pos.m_nX * CM_PIXEL_NUM , pos.m_nY * CM_PIXEL_NUM , CM_PIXEL_NUM ,CM_PIXEL_NUM);
}
void aoi_widget::draw_monster(const position &pos, const QColor &qc, QPixmap &canvas)
{
    QPainter painter(&canvas);
    painter.setBrush(qc); //定义用于填充形状的颜色和图案
    painter.drawRect(pos.m_nX * CM_PIXEL_NUM , pos.m_nY * CM_PIXEL_NUM , CM_PIXEL_NUM ,CM_PIXEL_NUM);
}
position aoi_widget::random(const position &pt)
{
    position curPos = pt;
    int rnd = rand() % 4;

    switch (rnd)
    {
    case 0:
    {
        curPos.m_nY--;
        break;
    }
    case 1:
    {
        curPos.m_nY++;
        break;
    }
    case 2:
    {
        curPos.m_nY--;
        break;
    }
    case 3:
    {
        curPos.m_nY++;
        break;
    }
    default:
        break;
    }

    if (curPos.m_nX < 0)
        curPos.m_nX = 0;
    if (curPos.m_nX >= m_stMapInfo.m_nWidth)
        curPos.m_nX--;
    if (curPos.m_nY < 0)
        curPos.m_nY = 0;
    if (curPos.m_nY >= m_stMapInfo.m_nHeight)
        curPos.m_nY--;

    return curPos;
}

void aoi_widget::refresh()
{
    if (m_stMapInfo.m_bMonsterMove)
    {
        OBJECTMGR.iter_all_object([this](Iobject *pObj) -> bool {
            if (pObj->is_monster())
            {
                position newPos = this->random(pObj->cur_pos());
                this->m_pAoi->move_to(pObj, newPos);
                pObj->set_position(newPos);
            }
            return true;
        });
    }

    if (m_stMapInfo.m_bCheckViewObject)
    {
        int32_t rnd = rand() % 100;
        if (rnd < 10)
        {
            msg_hander_time_record record(999999);
            std::vector<uint64_t> vecUids;
            m_pAoi->get_near_obj_uids(pRole,vecUids);
            for(auto &uid:vecUids)
            {
                Iobject * pObject = OBJECTMGR.get_object(uid);
                if(!pObject->is_role())
                {
                    QColor cl(0,0,0);
                    pObject->set_color(cl);
                }
            }
        }
    }
    update();
}
