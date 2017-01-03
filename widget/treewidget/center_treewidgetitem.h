#ifndef CENTERTREEWIDGETITEM_H
#define CENTERTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "bean/center/other_center.h"

class CenterTreeWidgetItem : public QTreeWidgetItem
{
public:
    CenterTreeWidgetItem(QTreeWidgetItem* parent, OtherCenter* center);
    ~CenterTreeWidgetItem();

private:
    QTreeWidgetItem* parent;
    OtherCenter* center;
};

#endif // CENTERTREEWIDGETITEM_H
