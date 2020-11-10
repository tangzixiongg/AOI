#include "aoi_widget.h"

#include <iostream>
#include <QPainter>
#include <QKeyEvent>

aoi_widget::aoi_widget(std::shared_ptr<aoi_interface> pAoi,const map_info& stMapInfo)
    :QWidget(nullptr),
      m_pAoi(pAoi),
      m_stMapInfo(stMapInfo)
{

}

aoi_widget::~aoi_widget()
{

}

void aoi_widget::paintEvent(QPaintEvent *event)
{
    return ;
}

void aoi_widget::keyPressEvent(QKeyEvent *event)
{
    return ;

}

void aoi_widget::draw_player(const position &pos, const QColor &qc ,QPixmap &canvas)
{
    return ;
}

void aoi_widget::refresh()
{

}
