#include "igmas_treewidgetitem.h"

IGMASTreeWidgetItem::IGMASTreeWidgetItem(IGMASStation* station, QTreeWidgetItem* parent) :
	QTreeWidgetItem(parent),
	station(station)
{
	this->setText(0, station->getStationName());
}

IGMASTreeWidgetItem::~IGMASTreeWidgetItem()
{
	delete station;
}

