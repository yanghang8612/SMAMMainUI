#include "igmas_treewidgetitem.h"

IGMASTreeWidgetItem::IGMASTreeWidgetItem(QTreeWidgetItem* parent, int type, iGMASStation* station) :
    QTreeWidgetItem(parent, type),
	station(station)
{
    this->setText(0, station->getMount());
    this->setIcon(0, QIcon(":/igmas_station"));
    this->setData(0, Qt::UserRole, QVariant::fromValue((void*) station));
}

IGMASTreeWidgetItem::~IGMASTreeWidgetItem()
{
	delete station;
}

