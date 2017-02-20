#ifndef CENTERTREEWIDGETITEM_H
#define CENTERTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "bean/center/other_center.h"

class CenterTreeWidgetItem : public QTreeWidgetItem
{
public:
    CenterTreeWidgetItem(QTreeWidgetItem* parent, int type, OtherCenter* center);
    ~CenterTreeWidgetItem();

private:
    OtherCenter* center;
};

#endif // CENTERTREEWIDGETITEM_H
