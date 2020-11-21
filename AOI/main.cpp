#include <ctime>
#include <iostream>
#include "aoi_widget.h"
#include "aoi_grid.h"
#include "view_manager.h"
#include "functions.h"
#include "base_define.h"
#include <stdint.h>
#include <QApplication>
#include <QWidget>

int32_t main(int32_t argc, char* argv[])
{
    QApplication app(argc, argv);
    std::string strFileName = "config.ini";

    if(argc >= 2)
    {
        strFileName = argv[1];
    }
    //地图信息
    map_info stMapinfo;
    int32_t nWidth = get_server_config_value("Config","nWidth",100,strFileName);
    int32_t nHeight = get_server_config_value("Config","nHeight",50,strFileName);
    int32_t nSquareSize = get_server_config_value("Config","nSquareSize",0,strFileName);
    int32_t nViewSize = get_server_config_value("Config","nViewSize",0,strFileName);
    stMapinfo = map_info(nWidth,nHeight,nSquareSize,nViewSize);
    stMapinfo.m_nNPCnums = get_server_config_value("Config","nNpcNums",20,strFileName);
    stMapinfo.m_nMonsternums = get_server_config_value("Config","nMonsterNums",500,strFileName);
    stMapinfo.m_bCheckViewObject = get_server_config_value("Config","bCheckViewObject",0,strFileName) == 1;
    stMapinfo.m_bMonsterMove = get_server_config_value("Config","bMonsterMove",0,strFileName) == 1;

    QWidget * w;
    aoi_interface * pAoi = make_aoi_grid();
    pAoi->init(stMapinfo);

    w = new aoi_widget(pAoi,stMapinfo);
    w->show();
    return app.exec();
}
