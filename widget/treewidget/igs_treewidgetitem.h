#ifndef IGSTREEWIDGETITEM_H
#define IGSTREEWIDGETITEM_H

#include <QtCore>
#include <QTreeWidgetItem>

#include "station/igs_station.h"

class IGSTreeWidgetItem : public QTreeWidgetItem
{
public:
	IGSTreeWidgetItem(IGSSTation* station, QTreeWidgetItem* parent);
	~IGSTreeWidgetItem();

private:
	IGSSTation* station;
};

#endif // IGSTREEWIDGETITEM_H
