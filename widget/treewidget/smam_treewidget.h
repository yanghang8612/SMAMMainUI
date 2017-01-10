#ifndef SMAMTREEWIDGET_H
#define SMAMTREEWIDGET_H

#include <QString>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QDomDocument>

#include "common.h"
#include "standard_treewidgetitem.h"
#include "igs_treewidgetitem.h"
#include "igmas_treewidgetitem.h"
#include "receiver_treewidgetitem.h"
#include "center_treewidgetitem.h"

class SMAMTreeWidget : public QObject
{
	Q_OBJECT

public:
    SMAMTreeWidget(QTreeWidget* tree, QVBoxLayout* container);

signals:

private slots:
	void showRightMenuAtBJ(QPoint pos);
	void showRightMenuAtXJ(QPoint pos);
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
    void addNewIGMASStationDialog(IGMASStation* station);

    void showModifyIGMASStationDialog();
    void modifyIGMASStation(IGMASStation* station);

    void deleteIGMASStation();

    void showAddNewIGSStationDialog();
    void addNewIGSStationDialog(IGSStation * station);

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

    QTreeWidget* tree;
    QTreeWidgetItem* standardStationTreeRoot;
    QTreeWidgetItem* iGMASStationTreeRoot;
    QTreeWidgetItem* iGSStatioinTreeRoot;
    QTreeWidgetItem* centerTreeRoot;

    QVBoxLayout* container;
	QWidget* currentContentWidget;
    QWidget* systemMonitorWidget;

    QDomDocument root;
    QDomNode standardStationRoot;
    QDomNode iGMASStationiRoot;
    QDomNode iGSStationRoot;
    QDomNode centerRoot;

	void initAtBJ();
	void initAtXJ();
	QDomDocument getRootFromXMLFile(const QString& filePath);
	void writeConfigFile();
};

#endif // SMAMTREEWIDGET_H
