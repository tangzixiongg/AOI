#pragma once

#include <QTimer>
#include <QWidget>

#include "aoi_interface.h"

class aoi_widget : public QWidget
{
    Q_OBJECT

public:
    aoi_widget(aoi_interface* pAoi,const map_info& stMapInfo);
    ~aoi_widget();
protected:

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
protected:
    void draw_player(const position &pos, const QColor &qc ,QPixmap &canvas);
    void draw_npc(const position &pos, const QColor &qc, QPixmap &canvas);
    void draw_monster(const position &pos, const QColor &qc, QPixmap &canvas);
    position random(const position &pt);

private slots:
    void refresh();

protected:

    QTimer * gameTimer;
    QPixmap bg_;
    aoi_interface* m_pAoi;
    map_info m_stMapInfo;
};
