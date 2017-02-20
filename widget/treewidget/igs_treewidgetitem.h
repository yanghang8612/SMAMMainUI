#ifndef IGSTREEWIDGETITEM_H
#define IGSTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "bean/station/igs_station.h"

class IGSTreeWidgetItem : public QTreeWidgetItem
{
public:
    IGSTreeWidgetItem(QTreeWidgetItem* parent, int type, IGSStation* station);
    ~IGSTreeWidgetItem();

private:
    IGSStation* station;
};

#endif // IGSTREEWIDGETITEM_H
