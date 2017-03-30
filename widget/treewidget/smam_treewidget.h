﻿#ifndef SMAMTREEWIDGET_H
#define SMAMTREEWIDGET_H

#include <QString>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QDomDocument>
#include <QBitArray>

#include "common.h"
#include "standard_treewidgetitem.h"
#include "igs_treewidgetitem.h"
#include "igmas_treewidgetitem.h"
#include "receiver_treewidgetitem.h"
#include "center_treewidgetitem.h"
#include "utilies/shared_buffer.h"

class SMAMTreeWidget : public QObject
{
	Q_OBJECT

public:
    SMAMTreeWidget(QTreeWidget* tree, QVBoxLayout* container);

    const QList<StandardStation*>& getStandardStationList() const;
    const QList<IGMASStation*>& getIGMASStationList() const;
    const QList<IGSStation*>& getIGSStationList() const;
    const QList<OtherCenter*>& getOtherCenterList() const;

    QList<int>& getComponentStateCheckIntervals();

private slots:
    void updateComponentStateCheckIntervals();

    void showRightMenu(QPoint pos);
    void addWidgetToContainer(QTreeWidgetItem* item);

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
    void addNewIGMASStation(IGMASStation* station);

    void showModifyIGMASStationDialog();
    void modifyIGMASStation(IGMASStation* station);

    void deleteIGMASStation();

    void showAddNewIGSStationDialog();
    void addNewIGSStation(IGSStation * station);

    void showModifyIGSStationDialog();
    void modifyIGSStation(IGSStation * station);

    void deleteIGSStation();

    void showAddNewCenterDialog();
    void addNewCenter(OtherCenter* center);

    void showModifyCenterDialog();
    void modifyCenter(OtherCenter* center);

    void deleteCenter();

private:
    QList<StandardStation*> standardStationList;
    QList<IGMASStation*> iGMASStationList;
    QList<IGSStation*> iGSStationList;
    QList<OtherCenter*> otherCenterList;
    SharedBuffer* receiverBuffer;
    SharedBuffer* iGMASStationBuffer;
    SharedBuffer* iGSStationBuffer;
    SharedBuffer* otherCenterBuffer;

    QTreeWidget* tree;
    QTreeWidgetItem* standardStationTreeRoot;
    QTreeWidgetItem* iGMASStationTreeRoot;
    QTreeWidgetItem* iGSStatioinTreeRoot;
    QTreeWidgetItem* otherCenterTreeRoot;
    QTreeWidgetItem* memoryTreeRoot;

    QVBoxLayout* container;
	QWidget* currentContentWidget;
    QWidget* systemMonitorWidget;

    QDomDocument root;
    QDomNode standardStationRoot;
    QDomNode iGMASStationRoot;
    QDomNode iGSStationRoot;
    QDomNode otherCenterRoot;
    QDomNode settingRoot;

    QBitArray receiverMemIdArray;
    QBitArray iGMASStationMemIdArray;

    QList<int> componentStateCheckIntervals;

	void initAtBJ();
	void initAtXJ();
	QDomDocument getRootFromXMLFile(const QString& filePath);
    void getComponentStateCheckIntervalFromXML();
	void writeConfigFile();
    void writeSharedBuffer();
    int findFreeReceiverMemId();
    int findFreeIGMASStationMemId();
};

#endif // SMAMTREEWIDGET_H
