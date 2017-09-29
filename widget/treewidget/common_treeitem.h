#ifndef COMMONTREEITEM_H
#define COMMONTREEITEM_H

#include <QTreeWidgetItem>

class CommonTreeItem : public QTreeWidgetItem
{
public:
    CommonTreeItem(int type, QString name, QString icon);
};

#endif // COMMONTREEITEM_H
