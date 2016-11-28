#ifndef IGMASTREEWIDGETITEM_H
#define IGMASTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "station/igmas_station.h"

class IGMASTreeWidgetItem : public QTreeWidgetItem
{
public:
	IGMASTreeWidgetItem(IGMASStation* station, QTreeWidgetItem* parent);
	~IGMASTreeWidgetItem();

private:
	IGMASStation* station;
};

#endif // IGMASTREEWIDGETITEM_H
