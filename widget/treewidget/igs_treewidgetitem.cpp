#include "igs_treewidgetitem.h"

IGSTreeWidgetItem::IGSTreeWidgetItem(IGSStation* station, QTreeWidgetItem* parent) :
	QTreeWidgetItem(parent),
	station(station)
{
	this->setText(0, station->getStationName());
}

IGSTreeWidgetItem::~IGSTreeWidgetItem()
{
	delete station;
}

