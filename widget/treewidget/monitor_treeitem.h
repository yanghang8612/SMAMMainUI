#ifndef MONITORTREEITEM_H
#define MONITORTREEITEM_H

#include <QTreeWidgetItem>

#include "bean/monitor_station.h"

class MonitorTreeItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

public:
    MonitorTreeItem(int type, MonitorStation* station);
    void updateTreeItem();

private slots:
    void handleStationStateChanged(int memID);

private:
    MonitorStation* station;
};

#endif // MONITORTREEITEM_H
