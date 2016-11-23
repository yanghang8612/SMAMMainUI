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
    utilies/cpumem_info.cpp \
    menu/base_menu.cpp \
    station/base_station.cpp \
    station/standard_station.cpp \
    user/base_user.cpp \
    station/receiver.cpp \
    dialog/add_standardstation_dialog.cpp \
    station/igs_station.cpp \
    station/igmas_station.cpp \
    widget/treewidget/igmas_treewidgetitem.cpp \
    widget/treewidget/igs_treewidgetitem.cpp \
    widget/treewidget/receiver_treewidgetitem.cpp \
    widget/treewidget/smam_treewidget.cpp \
    widget/treewidget/standard_treewidgetitem.cpp \
    widget/stationinfo_widget.cpp \
    widget/receiverinfo_widget.cpp \
    dialog/modify_standardstation_dialog.cpp \
    dialog/add_receiver_dialog.cpp \
    dialog/modify_receiver_dialog.cpp \
    db/database_access.cpp \
    widget/usermanager_widget.cpp \
    widget/useronline_widget.cpp \
    dialog/add_user_dialog.cpp \
    dialog/modify_user_dialog.cpp \
    dialog/view_user_dialog.cpp \
    widget/button/status_pushbutton.cpp \
    widget/softwarestatus_frame.cpp

HEADERS  += \
    smam_mainwindow.h \
    menu/xj_menu.h \
    menu/bj_menu.h \
    utilies/cpumem_info.h \
    menu/base_menu.h \
    station/base_station.h \
    station/standard_station.h \
    user/base_user.h \
    common.h \
    station/receiver.h \
    dialog/add_standardstation_dialog.h \
    station/igs_station.h \
    station/igmas_station.h \
    widget/treewidget/igmas_treewidgetitem.h \
    widget/treewidget/igs_treewidgetitem.h \
    widget/treewidget/receiver_treewidgetitem.h \
    widget/treewidget/smam_treewidget.h \
    widget/treewidget/standard_treewidgetitem.h \
    widget/stationinfo_widget.h \
    widget/receiverinfo_widget.h \
    dialog/modify_standardstation_dialog.h \
    dialog/add_receiver_dialog.h \
    dialog/modify_receiver_dialog.h \
    db/database_access.h \
    widget/usermanager_widget.h \
    widget/useronline_widget.h \
    dialog/add_user_dialog.h \
    dialog/modify_user_dialog.h \
    dialog/view_user_dialog.h \
    widget/button/status_pushbutton.h \
    widget/softwarestatus_frame.h

FORMS    += \
    smam_mainwindow.ui \
    dialog/add_standardstation_dialog.ui \
    widget/stationinfo_widget.ui \
    widget/receiverinfo_widget.ui \
    dialog/modify_standardstation_dialog.ui \
    dialog/add_receiver_dialog.ui \
    dialog/modify_receiver_dialog.ui \
    widget/usermanager_widget.ui \
    widget/useronline_widget.ui \
    dialog/add_user_dialog.ui \
    dialog/modify_user_dialog.ui \
    dialog/view_user_dialog.ui \
    widget/softwarestatus_frame.ui

RESOURCES += \
    res/icon.qrc \
    res/img.qrc

DISTFILES +=
