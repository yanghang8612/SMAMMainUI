#include "standard_treewidgetitem.h"

StandardTreeWidgetItem::StandardTreeWidgetItem(StandardStation* station, QTreeWidgetItem* parent) :
	QTreeWidgetItem(parent, 1),
	station(station), parent(parent)
{
	this->setText(0, station->getStationName());
}

StandardTreeWidgetItem::~StandardTreeWidgetItem()
{
	delete station;
}

