#include "monitor_treeitem.h"

#include "main_component_header.h"

MonitorTreeItem::MonitorTreeItem(int type, MonitorStation* station) :
    QTreeWidgetItem(type),
    station(station)
{
    this->setText(0, station->getDescription());
    if (station->getIsAvailable()) {
        this->setIcon(0, QIcon(":/monitor_station_green"));
    }
    else {
        this->setIcon(0, QIcon(":/monitor_station"));
    }

    registerSignalListener(this, "handleStationStateChanged(int)", "stationStateChanged(int)");
}

void MonitorTreeItem::handleStationStateChanged(int memID)
{
    if (memID == station->getMemID()) {
        switch (station->getState()) {
            case MonitorStation::CONNECTED:
            case MonitorStation::NORMAl:
                this->setIcon(0, QIcon(":/monitor_station_green"));
                break;
            case MonitorStation::NODATA:
                this->setIcon(0, QIcon(":/monitor_station_red"));
                break;
            case MonitorStation::UNCONNECTED:
                this->setIcon(0, QIcon(":/monitor_station"));
                break;
        }
    }
}
