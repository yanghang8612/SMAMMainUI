#include "common_treeitem.h"

CommonTreeItem::CommonTreeItem(int type, QString name, QString icon) :
    QTreeWidgetItem(type)
{
    this->setText(0, name);
    this->setIcon(0, QIcon(icon));
}

