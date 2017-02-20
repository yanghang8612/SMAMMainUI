#include "igs_treewidgetitem.h"

IGSTreeWidgetItem::IGSTreeWidgetItem(QTreeWidgetItem* parent, int type, IGSStation* station) :
    QTreeWidgetItem(parent, type),
	station(station)
{
    //this->setText(0, station->);
}

IGSTreeWidgetItem::~IGSTreeWidgetItem()
{
	delete station;
}

