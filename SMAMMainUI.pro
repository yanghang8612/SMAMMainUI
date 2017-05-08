#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T14:06:18
#
#-------------------------------------------------

QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMAMMainUI
TEMPLATE = app

SOURCES += \
    library_exportfunction.cpp \
    main.cpp \
    smam_mainwindow.cpp \
    #-#
    backend/dllstate_write_thread.cpp \
    #-#
    bean/center/base_center.cpp \
    bean/center/main_center.cpp \
    bean/center/other_center.cpp \
    #-#
    bean/station/base_station.cpp \
    bean/station/standard_station.cpp \
    bean/station/receiver.cpp \
    bean/station/igs_station.cpp \
    bean/station/igmas_station.cpp \
    #-#
    menu/xj_menu.cpp \
    menu/bj_menu.cpp \
    menu/base_menu.cpp \
    #-#
    utilies/cpumem_info.cpp \
    utilies/general_functions.cpp \
    utilies/shared_buffer.cpp \
    #-#
    widget/dialog/add_center_dialog.cpp \
    widget/dialog/modify_center_dialog.cpp \
    widget/dialog/add_receiver_dialog.cpp \
    widget/dialog/modify_receiver_dialog.cpp \
    widget/dialog/add_standardstation_dialog.cpp \
    widget/dialog/modify_standardstation_dialog.cpp \
    widget/dialog/add_igmasstation_dialog.cpp \
    widget/dialog/modify_igmasstation_dialog.cpp \
    widget/dialog/modify_component_state_check_intervals_dialog.cpp \
    #-#
    widget/graphicsitem/basenode.cpp \
    widget/graphicsitem/centernode.cpp \
    widget/graphicsitem/edge.cpp \
    widget/graphicsitem/receivernode.cpp \
    widget/graphicsitem/filenode.cpp \
    widget/graphicsitem/harddrivenode.cpp \
    widget/graphicsitem/usersnode.cpp \
    #-#
    widget/mid/systemmanager_widget.cpp \
    #-#
    widget/statuspopup/status_pushbutton.cpp \
    widget/statuspopup/softwarestatus_frame.cpp \
    #-#
    widget/treewidget/igmas_treewidgetitem.cpp \
    widget/treewidget/igs_treewidgetitem.cpp \
    widget/treewidget/receiver_treewidgetitem.cpp \
    widget/treewidget/smam_treewidget.cpp \
    widget/treewidget/standard_treewidgetitem.cpp \
    widget/treewidget/center_treewidgetitem.cpp \
    #-#
    widget/centerinfo_widget.cpp \
    widget/mainmonitor_widget.cpp \
    widget/receiverinfo_widget.cpp \
    widget/sharedmemoryinfo_widget.cpp \
    widget/standardstationinfo_widget.cpp \
    widget/igmasstationinfo_widget.cpp \
    widget/graphicsitem/standardnode.cpp \
    widget/graphicsitem/igmasnode.cpp \
    widget/graphicsitem/dmznode.cpp

HEADERS  += \
    common.h \
    main_component_header.h \
    smam_component_header.h \
    smam_mainwindow.h \
    #-#
    backend/dllstate_write_thread.h \
    #-#
    bean/center/base_center.h \
    bean/center/main_center.h \
    bean/center/other_center.h \
    #-#
    bean/station/base_station.h \
    bean/station/igmas_station.h \
    bean/station/igs_station.h \
    bean/station/receiver.h \
    bean/station/standard_station.h \
    #-#
    menu/base_menu.h \
    menu/xj_menu.h \
    menu/bj_menu.h \
    #-#
    utilies/cpumem_info.h \
    utilies/general_functions.h \
    utilies/shared_buffer.h \
    #-#
    widget/dialog/add_center_dialog.h \
    widget/dialog/modify_center_dialog.h \
    widget/dialog/add_igmasstation_dialog.h \
    widget/dialog/modify_igmasstation_dialog.h \
    widget/dialog/add_receiver_dialog.h \
    widget/dialog/modify_receiver_dialog.h \
    widget/dialog/add_standardstation_dialog.h \
    widget/dialog/modify_standardstation_dialog.h \
    widget/dialog/modify_component_state_check_intervals_dialog.h \
    #-#
    widget/graphicsitem/basenode.h \
    widget/graphicsitem/centernode.h \
    widget/graphicsitem/edge.h \
    widget/graphicsitem/receivernode.h \
    widget/graphicsitem/filenode.h \
    widget/graphicsitem/harddrivenode.h \
    widget/graphicsitem/usersnode.h \
    #-#
    widget/mid/systemmanager_widget.h \
    #-#
    widget/statuspopup/status_pushbutton.h \
    widget/statuspopup/softwarestatus_frame.h \
    #-#
    widget/treewidget/igmas_treewidgetitem.h \
    widget/treewidget/igs_treewidgetitem.h \
    widget/treewidget/receiver_treewidgetitem.h \
    widget/treewidget/smam_treewidget.h \
    widget/treewidget/standard_treewidgetitem.h \
    widget/treewidget/center_treewidgetitem.h \
    #-#
    widget/centerinfo_widget.h \
    widget/mainmonitor_widget.h \
    widget/receiverinfo_widget.h \
    widget/sharedmemoryinfo_widget.h \
    widget/standardstationinfo_widget.h \
    widget/igmasstationinfo_widget.h \
    widget/graphicsitem/standardnode.h \
    widget/graphicsitem/igmasnode.h \
    other_component_header.h \
    widget/graphicsitem/dmznode.h

FORMS    += \
    smam_mainwindow.ui \
    #-#
    widget/dialog/add_center_dialog.ui \
    widget/dialog/modify_center_dialog.ui \
    widget/dialog/add_standardstation_dialog.ui \
    widget/dialog/modify_standardstation_dialog.ui \
    widget/dialog/add_receiver_dialog.ui \
    widget/dialog/modify_receiver_dialog.ui \
    widget/dialog/add_igmasstation_dialog.ui \
    widget/dialog/modify_igmasstation_dialog.ui \
    widget/dialog/modify_component_state_check_intervals_dialog.ui \
    #-#
    widget/mid/systemmanager_widget.ui \
    #-#
    widget/statuspopup/softwarestatus_frame.ui \
    #-#
    widget/centerinfo_widget.ui \
    widget/mainmonitor_widget.ui \
    widget/receiverinfo_widget.ui \
    widget/sharedmemoryinfo_widget.ui \
    widget/standardstationinfo_widget.ui \
    widget/igmasstationinfo_widget.ui

RESOURCES += \
    res/icon.qrc \
    res/img.qrc \
    res/echarts.qrc
