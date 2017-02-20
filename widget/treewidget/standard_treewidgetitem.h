#ifndef STANDARDTREEWIDGETITEM_H
#define STANDARDTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "bean/station/standard_station.h"

class StandardTreeWidgetItem : public QTreeWidgetItem
{
public:
    StandardTreeWidgetItem(QTreeWidgetItem* parent, int type, StandardStation* station);
	~StandardTreeWidgetItem();

private:
	StandardStation* station;
};

#endif // STANDARDTREEWIDGETITEM_H
