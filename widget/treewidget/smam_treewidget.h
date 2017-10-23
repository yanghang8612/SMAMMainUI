#ifndef SMAMTREEWIDGET_H
#define SMAMTREEWIDGET_H

#include <QString>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QDomDocument>
#include <QBitArray>

#include "common.h"
#include "utilities/config_helper.h"
#include "widget/monitor/mainmonitor_widget.h"

class SMAMTreeWidget : public QObject
{
	Q_OBJECT

public:
    SMAMTreeWidget(QTreeWidget* tree, QVBoxLayout* container);

signals:
    void iGMASStationAdded(iGMASStationInBuffer* station);
    void iGMASStationStarted(int memID);
    void iGMASStationStoped(int memID);
    void iGMASStationModified(int memID);
    void iGMASStationDeleted(int memID);
    void iGMASDataCenterAdded(iGMASDataCenterInBuffer* dataCenter);
    void iGMASDataCenterModified(int centerID);
    void iGMASDataCenterDeleted(int centerID);
    void OtherCenterAdded(OtherCenterInBuffer* center);
    void OtherCenterModified(int centerID);
    void OtherCenterDeleted(int centerID);

private slots:
    void showRightMenu(QPoint pos);
    void handleItemClicked(QTreeWidgetItem* item);
    void handleItemDoubleClicked(QTreeWidgetItem* item);

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

    void showAddNewIGMASStationDialog();
    void addNewIGMASStation(iGMASStation* station);

    void startIGMASStation();
    void stopIGMASStation();

    void showModifyIGMASStationDialog();
    void modifyIGMASStation(iGMASStation* station);

    void deleteIGMASStation();

    void showAddNewIGMASDataCenterDialog();
    void addNewIGMASDataCenter(iGMASDataCenter* dataCenter);

    void showModifyIGMASDataCenterDialog();
    void modifyIGMASDataCenter(iGMASDataCenter* dataCenter);

    void deleteIGMASDataCenter();

    void showAddNewOtherCenterDialog();
    void addNewOtherCenter(OtherCenter* center);

    void showModifyOtherCenterDialog();
    void modifyOtherCenter(OtherCenter* center);

    void deleteOtherCenter();

private:
    QTreeWidget* tree;
    QTreeWidgetItem* standardStationTreeRoot;
    QTreeWidgetItem* iGMASStationTreeRoot;
    QTreeWidgetItem* iGMASDataCenterTreeRoot;
    QTreeWidgetItem* otherCenterTreeRoot;
    QTreeWidgetItem* memoryTreeRoot;
    QTreeWidgetItem* dmzTreeRoot;

    QVBoxLayout* container;
	QWidget* currentContentWidget;
    MainMonitorWidget* systemMonitorWidget;

	void initAtBJ();
    void initAtXJ();
};

#endif // SMAMTREEWIDGET_H
