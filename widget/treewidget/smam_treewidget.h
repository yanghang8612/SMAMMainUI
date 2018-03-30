#ifndef SMAMTREEWIDGET_H
#define SMAMTREEWIDGET_H

#include <QString>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QDomDocument>
#include <QBitArray>

#include "common.h"
#include "utilities/config_helper.h"
#include "widget/monitor/centermonitor_widget.h"
#include "widget/monitor/receivermonitor_widget.h"
#include "widget/monitor/stationmonitor_widget.h"
#include "widget/centerinfo_widget.h"
#include "widget/datacenter_widget.h"
#include "widget/monitorstationinfo_widget.h"
#include "widget/standardstationinfo_widget.h"
#include "widget/receiverinfo_widget.h"
#include "widget/sharedmemoryinfo_widget.h"

class SMAMTreeWidget : public QObject
{
	Q_OBJECT

public:
    SMAMTreeWidget(QTreeWidget* tree, QVBoxLayout* container);
    ~SMAMTreeWidget();

signals:
    void iGMASStationAdded(MonitorStationInBuffer* station);
    void iGMASStationStarted(int memID);
    void iGMASStationStoped(int memID);
    void iGMASStationModified(int memID);
    void iGMASStationDeleted(int memID);
    void DataCenterAdded(DataCenterInBuffer* dataCenter);
    void DataCenterModified(int centerID);
    void DataCenterDeleted(int centerID);
    void OtherCenterAdded(OtherCenterInBuffer* center);
    void OtherCenterModified(int centerID);
    void OtherCenterDeleted(int centerID);

private slots:
    void showRightMenu(QPoint pos);
    void handleItemClicked(QTreeWidgetItem* item);

	void showAddNewStandardStationDialog();
	void addNewStandardStation(StandardStation* station);

	void showModifyStandardStationDialog();
	void modifyStandardStation(StandardStation* station);

	void deleteStandardStation();

	void showAddNewReceiverDialog();
	void addNewReceiver(Receiver* receiver);

	void showModifyReceiverDialog();
	void modifyReceiver(Receiver* receiver);

	void deleteReceiver();

    void showAddNewMonitorStationDialog();
    void addNewMonitorStation(MonitorStation* station);

    void startMonitorStation();
    void stopMonitorStation();

    void showModifyMonitorStationDialog();
    void modifyMonitorStation(MonitorStation* station);

    void deleteMonitorStation();

    void showAddNewDataCenterDialog();
    void addNewDataCenter(DataCenter* dataCenter);

    void showModifyDataCenterDialog();
    void modifyDataCenter(DataCenter* dataCenter);

    void deleteDataCenter();

    void showAddNewOtherCenterDialog();
    void addNewOtherCenter(OtherCenter* center);

    void showModifyOtherCenterDialog();
    void modifyOtherCenter(OtherCenter* center);

    void deleteOtherCenter();

private:
    QTreeWidget* tree;
    QTreeWidgetItem* standardStationTreeRoot;
    QTreeWidgetItem* monitorStationTreeRoot;
    QTreeWidgetItem* dataCenterTreeRoot;
    QTreeWidgetItem* otherCenterTreeRoot;
    QTreeWidgetItem* memoryTreeRoot;
    QTreeWidgetItem* dmzTreeRoot;

    QVBoxLayout* container;
	QWidget* currentContentWidget;
    CenterMonitorWidget* centerMonitorWidget;
    ReceiverMonitorWidget* receiverMonitorWidget;
    StationMonitorWidget* stationMonitorWidget;
    CenterInfoWidget* centerInfoWidget;
    DataCenterWidget* dataCenterWidget;
    MonitorStationInfoWidget* monitorStationInfoWidget;
    ReceiverInfoWidget* receiverInfoWidget;
    SharedMemoryInfoWidget* sharedMemoryInfoWidget;
    StandardStationInfoWidget* standardStationInfoWidget;

	void initAtBJ();
    void initAtXJ();
};

#endif // SMAMTREEWIDGET_H
