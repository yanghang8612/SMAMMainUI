#include "standard_treewidgetitem.h"

StandardTreeWidgetItem::StandardTreeWidgetItem(QTreeWidgetItem* parent, StandardStation* station) :
	QTreeWidgetItem(parent, 01),
	parent(parent), station(station)
{
	this->setText(0, station->getStationName());
	this->setIcon(0, QIcon(":/standard_station"));
	this->setData(0, Qt::UserRole, QVariant::fromValue((void*) station));
}

StandardTreeWidgetItem::~StandardTreeWidgetItem()
{
	delete station;
}

