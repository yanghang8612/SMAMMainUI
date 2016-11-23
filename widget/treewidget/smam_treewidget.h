#ifndef SMAMTREEWIDGET_H
#define SMAMTREEWIDGET_H

#include <QtCore>
#include <QTreeWidget>
#include <QtXml/QDomDocument>

#include "common.h"
#include "standard_treewidgetitem.h"
#include "igs_treewidgetitem.h"
#include "igmas_treewidgetitem.h"
#include "receiver_treewidgetitem.h"

class SMAMTreeWidget : public QObject
{
	Q_OBJECT

public:
	SMAMTreeWidget(QTreeWidget* tree, DeploymentType::Value type);

signals:

private slots:
	void showRightMenuAtBJ(QPoint pos);
	void showRightMenuAtXJ(QPoint pos);

private:
	QTreeWidget* tree;
	DeploymentType::Value type;
	QList<StandardStation*> standardStations;
	QList<IGMASStation*> iGMASStations;
	QList<IGSSTation*> iGSStations;

	void initAtBJ();
	void initAtXJ();
	QDomElement getRootFromXMLFile(const QString& filePath);
};

#endif // SMAMTREEWIDGET_H
