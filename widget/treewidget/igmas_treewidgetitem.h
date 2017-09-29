#ifndef IGMASTREEWIDGETITEM_H
#define IGMASTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "bean/station/igmas_station.h"

class IGMASTreeWidgetItem : public QTreeWidgetItem
{
public:
    IGMASTreeWidgetItem(QTreeWidgetItem* parent, int type, iGMASStation* station);
    ~IGMASTreeWidgetItem();

private:
	iGMASStation* station;
};

#endif // IGMASTREEWIDGETITEM_H
