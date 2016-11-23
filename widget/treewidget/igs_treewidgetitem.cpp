#include "igs_treewidgetitem.h"

IGSTreeWidgetItem::IGSTreeWidgetItem(IGSSTation* station, QTreeWidgetItem* parent) :
	QTreeWidgetItem(parent),
	station(station)
{
	this->setText(0, station->getStationName());
}

IGSTreeWidgetItem::~IGSTreeWidgetItem()
{
	delete station;
}

