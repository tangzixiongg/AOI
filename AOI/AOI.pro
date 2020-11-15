QT += widgets

SOURCES += \
    main.cpp \
    monster.cpp \
    npc.cpp \
    object_mgr.cpp \
    role.cpp \
    functions.cpp \
    aoi_widget.cpp \
    singleton.inl \
    aoi_grid.cpp \
    view_manager.cpp

HEADERS += \
    Iobject.h \
    aoi_interface.h \
    base_define.h \
    monster.h \
    npc.h \
    object_mgr.h \
    role.h \
    functions.h \
    aoi_widget.h \
    singleton.h \
    aoi_grid.h \
    view_manager.h

DEFINES-= UNICODE
