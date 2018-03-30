#include <QStringList>
#include <QDebug>

#include "monitor_station.h"
#include "common.h"
#include "utilities/general_functions.h"

extern void* monitorStationSharedBufferPointer;

MonitorStation::MonitorStation() : memID(0), state(UNCONNECTED)
{
    MonitorStationInBuffer* item = (MonitorStationInBuffer*)((char*)monitorStationSharedBufferPointer + 4);
    for (int i = 0; i < MONITORSTATION_MAXITEMCOUNT; i++, item++) {
        if (item->memID == 0) {
            bufferItem = item;
            break;
        }
    }
    setIsAvailable(false);
    (*((int*)monitorStationSharedBufferPointer))++;
}

MonitorStation::~MonitorStation()
{
    setMemID(0);
    (*((int*)monitorStationSharedBufferPointer))--;
}

QString MonitorStation::getDescription()
{
    return stationName + "(" + mountPoint + ")";
}

int MonitorStation::getMemID() const
{
    return memID;
}

void MonitorStation::setMemID(int value)
{
    memID = value;
    bufferItem->memID = value;
}

void MonitorStation::setMemID(const QString& value)
{
    setMemID(value.toInt());
}

bool MonitorStation::getIsAvailable() const
{
    return isAvailable;
}

void MonitorStation::setIsAvailable(bool value)
{
    isAvailable = value;
    bufferItem->isAvailable = value;
}

void MonitorStation::setIsAvailable(const QString& value)
{
    setIsAvailable(value == "true");
}

QString MonitorStation::getStationName() const
{
    return stationName;
}

void MonitorStation::setStationName(const QString& value)
{
    stationName = value;
    qstrcpy(bufferItem->stationName, value.toStdString().c_str());
}

QString MonitorStation::getMountPoint() const
{
    return mountPoint;
}

void MonitorStation::setMountPoint(const QString& value)
{
    mountPoint = value;
    qstrcpy(bufferItem->mountPoint, value.toStdString().c_str());
}

DMS MonitorStation::getLongitude() const
{
    return longitude;
}

void MonitorStation::setLongitude(const DMS& value)
{
    longitude = value;
    bufferItem->longitude = value;
}

void MonitorStation::setLongitude(const QString& value)
{
    setLongitude(GeneralFunctions::convertQStringToDMS(value));
}

DMS MonitorStation::getLatitude() const
{
    return latitude;
}

void MonitorStation::setLatitude(const DMS& value)
{
    latitude = value;
    bufferItem->latitude = value;
}

void MonitorStation::setLatitude(const QString& value)
{
    setLatitude(GeneralFunctions::convertQStringToDMS(value));
}

double MonitorStation::getHeight() const
{
    return height;
}

void MonitorStation::setHeight(double value)
{
    height = value;
}

void MonitorStation::setHeight(const QString& value)
{
    setHeight(value.toDouble());
}

QString MonitorStation::getDetail() const
{
    return detail;
}

void MonitorStation::setDetail(const QString& value)
{
    detail = value;
    qstrcpy(bufferItem->stationDetail, value.toStdString().c_str());
}

QString MonitorStation::getDataCenters() const
{
    return dataCenters;
}

void MonitorStation::setDataCenters(const QString& value)
{
    dataCenters = value;
    qstrcpy(bufferItem->dataCenters, value.toStdString().c_str());
}

void MonitorStation::deleteDataCenter(int centerID)
{
    QStringList list = dataCenters.split(",", QString::SkipEmptyParts);
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == QString::number(centerID)) {
            list.removeAt(i);
            QString newDataCenters = "";
            for (int i = 0; i < list.size(); i++) {
                newDataCenters += (list[i] + ",");
            }
            setDataCenters(newDataCenters);
            break;
        }
    }
}

MonitorStation::StationState MonitorStation::getState() const
{
    return state;
}

void MonitorStation::setState(const StationState& value)
{
    state = value;
}

MonitorStationInBuffer*MonitorStation::getBufferItem()
{
    return bufferItem;
}

MonitorStationInBuffer MonitorStation::toMonitorStationInBuffer()
{
    MonitorStationInBuffer bufferItem;
    bufferItem.memID = memID;
    bufferItem.isAvailable = true;
    qstrcpy(bufferItem.stationName, stationName.toStdString().c_str());
    qstrcpy(bufferItem.mountPoint, mountPoint.toStdString().c_str());
    bufferItem.longitude = longitude;
    bufferItem.latitude = latitude;
    bufferItem.height = height;
    qstrcpy(bufferItem.stationDetail, detail.toStdString().c_str());
    qstrcpy(bufferItem.dataCenters, dataCenters.toStdString().c_str());
    return bufferItem;
}
