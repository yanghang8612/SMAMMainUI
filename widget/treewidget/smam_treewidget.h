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

class SMAMTreeWidget : public QObject
{
	Q_OBJECT

public:
	SMAMTreeWidget(QTreeWidget* tree, QVBoxLayout* container, DeploymentType::Value type);

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

public:
	QList<StandardStation*> standardStationList;

private:
	QTreeWidget* tree;
	QTreeWidgetItem* stationTreeRoot;
	QTreeWidgetItem* userTreeRoot;

	QVBoxLayout* container;
	DeploymentType::Value type;
	QWidget* currentContentWidget;
    QWidget* systemMonitorWidget;

	QDomDocument root;

	void initAtBJ();
	void initAtXJ();
	QDomDocument getRootFromXMLFile(const QString& filePath);
	void writeConfigFile();
};

#endif // SMAMTREEWIDGET_H
