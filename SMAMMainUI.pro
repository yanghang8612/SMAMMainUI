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
    systemmanager_widget.cpp \
    #-#
    backend/dllstate_write_thread.cpp \
    #-#
    bean/igmas_datacenter.cpp \
    bean/igmas_station.cpp \
    bean/main_center.cpp \
    bean/other_center.cpp \
    bean/receiver.cpp \
    bean/standard_station.cpp \
    #-#
    menu/xj_menu.cpp \
    menu/bj_menu.cpp \
    menu/base_menu.cpp \
    #-#
    utilities/config_helper.cpp \
    utilities/cpumem_info.cpp \
    utilities/general_functions.cpp \
    utilities/shared_buffer.cpp \
    #-#
    #-#
    widget/monitor/mainmonitor_widget.cpp \
    widget/monitor/item/basenode.cpp \
    widget/monitor/item/centernode.cpp \
    widget/monitor/item/edge.cpp \
    widget/monitor/item/filenode.cpp \
    widget/monitor/item/harddrivenode.cpp \
    widget/monitor/item/igmasnode.cpp \
    widget/monitor/item/receivernode.cpp \
    widget/monitor/item/standardnode.cpp \
    widget/monitor/item/usersnode.cpp \
    #-#
    widget/statuspopup/status_pushbutton.cpp \
    widget/statuspopup/softwarestatus_frame.cpp \
    #-#
    widget/treewidget/smam_treewidget.cpp \
    widget/treewidget/common_treeitem.cpp \
    #-#
    widget/centerinfo_widget.cpp \
    widget/igmasstationinfo_widget.cpp \
    widget/receiverinfo_widget.cpp \
    widget/sharedmemoryinfo_widget.cpp \
    widget/standardstationinfo_widget.cpp \
    widget/dialog/othercenter_edit_dialog.cpp \
    widget/dialog/igmasstation_edit_dialog.cpp \
    widget/dialog/receiver_edit_dialog.cpp \
    widget/dialog/standardstation_edit_dialog.cpp \
    widget/dialog/componentstatecheckintervals_edit_dialog.cpp \
    widget/igmasdatacenter_widget.cpp \
    widget/dialog/igmasdatacenter_edit_dialog.cpp \
    widget/monitor/item/datastatenode.cpp \
    widget/statuspopup/datatransferstate_frame.cpp

HEADERS  += \
    common.h \
    main_component_header.h \
    other_component_header.h \
    smam_component_header.h \
    smam_mainwindow.h \
    systemmanager_widget.h \
    #-#
    backend/dllstate_write_thread.h \
    #-#
    bean/igmas_datacenter.h \
    bean/igmas_station.h \
    bean/main_center.h \
    bean/other_center.h \
    bean/receiver.h \
    bean/standard_station.h \
    #-#
    menu/base_menu.h \
    menu/xj_menu.h \
    menu/bj_menu.h \
    #-#
    utilities/config_helper.h \
    utilities/cpumem_info.h \
    utilities/general_functions.h \
    utilities/shared_buffer.h \
    #-#
    #-#
    widget/monitor/mainmonitor_widget.h \
    widget/monitor/item/basenode.h \
    widget/monitor/item/centernode.h \
    widget/monitor/item/edge.h \
    widget/monitor/item/filenode.h \
    widget/monitor/item/harddrivenode.h \
    widget/monitor/item/igmasnode.h \
    widget/monitor/item/receivernode.h \
    widget/monitor/item/standardnode.h \
    widget/monitor/item/usersnode.h \
    #-#
    widget/statuspopup/status_pushbutton.h \
    widget/statuspopup/softwarestatus_frame.h \
    #-#
    widget/treewidget/common_treeitem.h \
    widget/treewidget/smam_treewidget.h \
    #-#
    widget/centerinfo_widget.h \
    widget/igmasstationinfo_widget.h \
    widget/receiverinfo_widget.h \
    widget/sharedmemoryinfo_widget.h \
    widget/standardstationinfo_widget.h \
    widget/dialog/othercenter_edit_dialog.h \
    widget/dialog/igmasstation_edit_dialog.h \
    widget/dialog/receiver_edit_dialog.h \
    widget/dialog/standardstation_edit_dialog.h \
    widget/dialog/componentstatecheckintervals_edit_dialog.h \
    widget/igmasdatacenter_widget.h \
    widget/dialog/igmasdatacenter_edit_dialog.h \
    widget/monitor/item/datastatenode.h \
    widget/statuspopup/datatransferstate_frame.h

FORMS    += \
    smam_mainwindow.ui \
    systemmanager_widget.ui \
    #-#
    #-#
    widget/monitor/mainmonitor_widget.ui \
    #-#
    widget/statuspopup/softwarestatus_frame.ui \
    #-#
    widget/centerinfo_widget.ui \
    widget/igmasstationinfo_widget.ui \
    widget/receiverinfo_widget.ui \
    widget/sharedmemoryinfo_widget.ui \
    widget/standardstationinfo_widget.ui \
    widget/dialog/othercenter_edit_dialog.ui \
    widget/dialog/igmasstation_edit_dialog.ui \
    widget/dialog/receiver_edit_dialog.ui \
    widget/dialog/standardstation_edit_dialog.ui \
    widget/dialog/componentstatecheckintervals_edit_dialog.ui \
    widget/igmasdatacenter_widget.ui \
    widget/dialog/igmasdatacenter_edit_dialog.ui \
    widget/statuspopup/datatransferstate_frame.ui

RESOURCES += \
    res/icon.qrc \
    res/img.qrc
