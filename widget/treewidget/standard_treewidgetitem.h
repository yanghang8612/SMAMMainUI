#ifndef STANDARDTREEWIDGETITEM_H
#define STANDARDTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "station/standard_station.h"

class StandardTreeWidgetItem : public QTreeWidgetItem
{
public:
	StandardTreeWidgetItem(QTreeWidgetItem* parent = 0, StandardStation* station = 0);
	~StandardTreeWidgetItem();

private:
	QTreeWidgetItem* parent;
	StandardStation* station;
};

#endif // STANDARDTREEWIDGETITEM_H
