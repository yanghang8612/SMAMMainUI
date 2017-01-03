#include "center_treewidgetitem.h"

CenterTreeWidgetItem::CenterTreeWidgetItem(QTreeWidgetItem* parent, OtherCenter* center) :
    QTreeWidgetItem(parent, 21),
    parent(parent), center(center)
{
    this->setText(0, center->getCenterName());
    this->setIcon(0, QIcon(":/other_center"));
    this->setData(0, Qt::UserRole, QVariant::fromValue((void*) center));
}

CenterTreeWidgetItem::~CenterTreeWidgetItem()
{
    delete center;
}

