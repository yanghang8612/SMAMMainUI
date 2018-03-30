#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T14:06:18
#
#-------------------------------------------------

QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMAMMainUI
TEMPLATE = lib

SOURCES += \
    library_exportfunction.cpp \
    main.cpp \
    smam_mainwindow.cpp \
    systemmanager_widget.cpp \
    #-#
    backend/dllstate_write_thread.cpp \
    #-#
    bean/data_center.cpp \
    bean/main_center.cpp \
    bean/monitor_station.cpp \
    bean/other_center.cpp \
    bean/receiver.cpp \
    bean/standard_station.cpp \
    #-#
    utilities/config_helper.cpp \
    utilities/cpumem_info.cpp \
    utilities/general_functions.cpp \
    utilities/shared_buffer.cpp \
    #-#
    widget/dialog/componentstatecheckintervals_edit_dialog.cpp \
    widget/dialog/datacenter_edit_dialog.cpp \
    widget/dialog/datacenter_select_dialog.cpp \
    widget/dialog/monitorstation_edit_dialog.cpp \
    widget/dialog/othercenter_edit_dialog.cpp \
    widget/dialog/receiver_edit_dialog.cpp \
    widget/dialog/standardstation_edit_dialog.cpp \
    #-#
    widget/monitor/item/basenode.cpp \
    widget/monitor/item/datastatenode.cpp \
    widget/monitor/item/edge.cpp \
    widget/monitor/item/filenode.cpp \
    widget/monitor/item/maincenternode.cpp \
    widget/monitor/item/monitornode.cpp \
    widget/monitor/item/othercenternode.cpp \
    widget/monitor/item/receivernode.cpp \
    widget/monitor/item/standardnode.cpp \
    #-#
    widget/plugin/draggablelist_widget.cpp \
    #-#
    widget/popup/datatransferstate_frame.cpp \
    widget/popup/softwarestatus_frame.cpp \
    widget/popup/status_pushbutton.cpp \
    #-#
    widget/treewidget/smam_treewidget.cpp \
    widget/treewidget/common_treeitem.cpp \
    #-#
    widget/centerinfo_widget.cpp \
    widget/datacenter_widget.cpp \
    widget/monitorstationinfo_widget.cpp \
    widget/receiverinfo_widget.cpp \
    widget/sharedmemoryinfo_widget.cpp \
    widget/standardstationinfo_widget.cpp \
    widget/monitor/stationmonitor_widget.cpp \
    widget/monitor/receivermonitor_widget.cpp \
    widget/monitor/centermonitor_widget.cpp \
    widget/monitor/item/terminalnode.cpp \
    widget/monitor/item/networknode.cpp \
    widget/treewidget/monitor_treeitem.cpp

HEADERS += \
    common.h \
    main_component_header.h \
    other_component_header.h \
    smam_component_header.h \
    smam_mainwindow.h \
    systemmanager_widget.h \
    #-#
    backend/dllstate_write_thread.h \
    #-#
    bean/data_center.h \
    bean/main_center.h \
    bean/monitor_station.h \
    bean/other_center.h \
    bean/receiver.h \
    bean/standard_station.h \
    #-#
    utilities/config_helper.h \
    utilities/cpumem_info.h \
    utilities/general_functions.h \
    utilities/shared_buffer.h \
    #-#
    widget/dialog/componentstatecheckintervals_edit_dialog.h \
    widget/dialog/datacenter_edit_dialog.h \
    widget/dialog/datacenter_select_dialog.h \
    widget/dialog/monitorstation_edit_dialog.h \
    widget/dialog/othercenter_edit_dialog.h \
    widget/dialog/receiver_edit_dialog.h \
    widget/dialog/standardstation_edit_dialog.h \
    #-#
    widget/monitor/item/basenode.h \
    widget/monitor/item/datastatenode.h \
    widget/monitor/item/edge.h \
    widget/monitor/item/filenode.h \
    widget/monitor/item/maincenternode.h \
    widget/monitor/item/monitornode.h \
    widget/monitor/item/othercenternode.h \
    widget/monitor/item/receivernode.h \
    widget/monitor/item/standardnode.h \
    #-#
    widget/plugin/draggablelist_widget.h \
    #-#
    widget/popup/datatransferstate_frame.h \
    widget/popup/softwarestatus_frame.h \
    widget/popup/status_pushbutton.h \
    #-#
    widget/treewidget/common_treeitem.h \
    widget/treewidget/smam_treewidget.h \
    #-#
    widget/centerinfo_widget.h \
    widget/datacenter_widget.h \
    widget/monitorstationinfo_widget.h \
    widget/receiverinfo_widget.h \
    widget/sharedmemoryinfo_widget.h \
    widget/standardstationinfo_widget.h \
    widget/monitor/stationmonitor_widget.h \
    widget/monitor/receivermonitor_widget.h \
    widget/monitor/centermonitor_widget.h \
    widget/monitor/item/terminalnode.h \
    widget/monitor/item/networknode.h \
    widget/treewidget/monitor_treeitem.h

FORMS += \
    smam_mainwindow.ui \
    systemmanager_widget.ui \
    #-#
    widget/dialog/componentstatecheckintervals_edit_dialog.ui \
    widget/dialog/monitorstation_edit_dialog.ui \
    widget/dialog/datacenter_select_dialog.ui \
    widget/dialog/datacenter_edit_dialog.ui \
    widget/dialog/othercenter_edit_dialog.ui \
    widget/dialog/receiver_edit_dialog.ui \
    widget/dialog/standardstation_edit_dialog.ui \
    #-#
    #-#
    widget/popup/datatransferstate_frame.ui \
    widget/popup/softwarestatus_frame.ui \
    #-#
    widget/centerinfo_widget.ui \
    widget/datacenter_widget.ui \
    widget/monitorstationinfo_widget.ui \
    widget/receiverinfo_widget.ui \
    widget/sharedmemoryinfo_widget.ui \
    widget/standardstationinfo_widget.ui \
    widget/monitor/stationmonitor_widget.ui \
    widget/monitor/receivermonitor_widget.ui \
    widget/monitor/centermonitor_widget.ui

RESOURCES += \
    res/icon.qrc \
    res/img.qrc
