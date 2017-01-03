#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T14:06:18
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMAMMainUI
TEMPLATE = app


SOURCES += main.cpp \
    smam_mainwindow.cpp \
    menu/xj_menu.cpp \
    menu/bj_menu.cpp \
    menu/base_menu.cpp \
    utilies/cpumem_info.cpp \
    utilies/general_functions.cpp \
    db/database_access.cpp \
    bean/center/base_center.cpp \
    bean/center/main_center.cpp \
    bean/center/other_center.cpp \
    bean/station/base_station.cpp \
    bean/station/standard_station.cpp \
    bean/station/receiver.cpp \
    bean/station/igs_station.cpp \
    bean/station/igmas_station.cpp \
    bean/user/base_user.cpp \
    widget/mainmonitor_widget.cpp \
    widget/stationinfo_widget.cpp \
    widget/receiverinfo_widget.cpp \
    widget/usermanager_widget.cpp \
    widget/useronline_widget.cpp \
    widget/dialog/add_standardstation_dialog.cpp \
    widget/dialog/modify_standardstation_dialog.cpp \
    widget/dialog/add_receiver_dialog.cpp \
    widget/dialog/modify_receiver_dialog.cpp \
    widget/dialog/add_user_dialog.cpp \
    widget/dialog/modify_user_dialog.cpp \
    widget/dialog/view_user_dialog.cpp \
    widget/treewidget/igmas_treewidgetitem.cpp \
    widget/treewidget/igs_treewidgetitem.cpp \
    widget/treewidget/receiver_treewidgetitem.cpp \
    widget/treewidget/smam_treewidget.cpp \
    widget/treewidget/standard_treewidgetitem.cpp \
    widget/treewidget/center_treewidgetitem.cpp \
    widget/statuspopup/status_pushbutton.cpp \
    widget/statuspopup/softwarestatus_frame.cpp \
    widget/mid/systemmanager_widget.cpp \
    widget/graphicsitem/basenode.cpp \
    widget/graphicsitem/centernode.cpp \
    widget/graphicsitem/edge.cpp \
    widget/graphicsitem/receivernode.cpp \
    widget/graphicsitem/stationnode.cpp \
    widget/graphicsitem/filenode.cpp \
    widget/graphicsitem/harddrivenode.cpp \
    widget/graphicsitem/usersnode.cpp

HEADERS  += \
    smam_mainwindow.h \
    menu/xj_menu.h \
    menu/bj_menu.h \
    menu/base_menu.h \
    utilies/cpumem_info.h \
    utilies/general_functions.h \
    db/database_access.h \
    bean/center/base_center.h \
    bean/center/main_center.h \
    bean/center/other_center.h \
    bean/station/base_station.h \
    bean/station/standard_station.h \
    bean/station/receiver.h \
    bean/station/igs_station.h \
    bean/station/igmas_station.h \
    bean/user/base_user.h \
    widget/mainmonitor_widget.h \
    widget/stationinfo_widget.h \
    widget/receiverinfo_widget.h \
    widget/usermanager_widget.h \
    widget/useronline_widget.h \
    widget/dialog/add_standardstation_dialog.h \
    widget/dialog/modify_standardstation_dialog.h \
    widget/dialog/add_receiver_dialog.h \
    widget/dialog/modify_receiver_dialog.h \
    widget/dialog/add_user_dialog.h \
    widget/dialog/modify_user_dialog.h \
    widget/dialog/view_user_dialog.h \
    widget/treewidget/igmas_treewidgetitem.h \
    widget/treewidget/igs_treewidgetitem.h \
    widget/treewidget/receiver_treewidgetitem.h \
    widget/treewidget/smam_treewidget.h \
    widget/treewidget/standard_treewidgetitem.h \
    widget/treewidget/center_treewidgetitem.h \
    widget/statuspopup/status_pushbutton.h \
    widget/statuspopup/softwarestatus_frame.h \
    widget/mid/systemmanager_widget.h \
    widget/graphicsitem/basenode.h \
    widget/graphicsitem/centernode.h \
    widget/graphicsitem/edge.h \
    widget/graphicsitem/receivernode.h \
    widget/graphicsitem/stationnode.h \
    widget/graphicsitem/filenode.h \
    widget/graphicsitem/harddrivenode.h \
    widget/graphicsitem/usersnode.h

FORMS    += \
    smam_mainwindow.ui \
    widget/mainmonitor_widget.ui \
    widget/stationinfo_widget.ui \
    widget/receiverinfo_widget.ui \
    widget/usermanager_widget.ui \
    widget/useronline_widget.ui \
    widget/dialog/add_standardstation_dialog.ui \
    widget/dialog/modify_standardstation_dialog.ui \
    widget/dialog/add_receiver_dialog.ui \
    widget/dialog/modify_receiver_dialog.ui \
    widget/dialog/add_user_dialog.ui \
    widget/dialog/modify_user_dialog.ui \
    widget/dialog/view_user_dialog.ui \
    widget/statuspopup/softwarestatus_frame.ui \
    widget/mid/systemmanager_widget.ui

RESOURCES += \
    res/icon.qrc \
    res/img.qrc \
    res/echarts.qrc
