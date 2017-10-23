#include <QStringList>

#include "igmas_station.h"
#include "common.h"

extern void* iGMASStationSharedBufferPointer;

iGMASStation::iGMASStation() : memID(0)
{
    iGMASStationInBuffer* item = (iGMASStationInBuffer*)((char*)iGMASStationSharedBufferPointer + 4);
    for (int i = 0; i < IGMASSTATION_MAXITEMCOUNT; i++, item++) {
        if (item->memID == 0) {
            bufferItem = item;
            break;
        }
    }
    (*((int*)iGMASStationSharedBufferPointer))++;
}

iGMASStation::~iGMASStation()
{
    bufferItem->memID = 0;
    (*((int*)iGMASStationSharedBufferPointer))--;
}

QString iGMASStation::getDescription()
{
    return stationName + "(" + mountPoint + ")";
}

int iGMASStation::getMemID() const
{
    return memID;
}

void iGMASStation::setMemID(int value)
{
    memID = value;
    bufferItem->memID = value;
}

void iGMASStation::setMemID(const QString& value)
{
    setMemID(value.toInt());
}

bool iGMASStation::getIsAvailable() const
{
    return isAvailable;
}

void iGMASStation::setIsAvailable(bool value)
{
    isAvailable = value;
    bufferItem->isAvailable = value;
}

void iGMASStation::setIsAvailable(const QString& value)
{
    setIsAvailable(value == "true");
}

QString iGMASStation::getStationName() const
{
    return stationName;
}

void iGMASStation::setStationName(const QString& value)
{
    stationName = value;
    qMemSet(bufferItem->stationName, 0, sizeof(bufferItem->stationName));
    qMemCopy(bufferItem->stationName, value.toStdString().c_str(), value.length());
}

QString iGMASStation::getMountPoint() const
{
    return mountPoint;
}

void iGMASStation::setMountPoint(const QString& value)
{
    mountPoint = value;
    qMemSet(bufferItem->mountPoint, 0, sizeof(bufferItem->mountPoint));
    qMemCopy(bufferItem->mountPoint, value.toStdString().c_str(), value.length());
}

double iGMASStation::getLongitude() const
{
    return longitude;
}

void iGMASStation::setLongitude(double value)
{
    longitude = value;
    bufferItem->longitude = value;
}

void iGMASStation::setLongitude(const QString& value)
{
    setLongitude(value.toDouble());
}

double iGMASStation::getLatitude() const
{
    return latitude;
}

void iGMASStation::setLatitude(double value)
{
    latitude = value;
    bufferItem->latitude = value;
}

void iGMASStation::setLatitude(const QString& value)
{
    setLatitude(value.toDouble());
}

double iGMASStation::getHeight() const
{
    return height;
}

void iGMASStation::setHeight(double value)
{
    height = value;
    bufferItem->height = value;
}

void iGMASStation::setHeight(const QString& value)
{
    setHeight(value.toDouble());
}

QString iGMASStation::getDetail() const
{
    return detail;
}

void iGMASStation::setDetail(const QString& value)
{
    detail = value;
    qMemSet(bufferItem->stationDetail, 0, sizeof(bufferItem->stationDetail));
    qMemCopy(bufferItem->stationDetail, value.toStdString().c_str(), value.length());
}

QString iGMASStation::getDataCenters() const
{
    return dataCenters;
}

void iGMASStation::setDataCenters(const QString& value)
{
    dataCenters = value;
    qMemSet(bufferItem->dataCenters, 0, sizeof(bufferItem->stationDetail));
    qMemCopy(bufferItem->dataCenters, value.toStdString().c_str(), value.length());
}

void iGMASStation::deleteDataCenter(int centerID)
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

iGMASStationInBuffer*iGMASStation::getBufferItem()
{
    return bufferItem;
}

iGMASStationInBuffer iGMASStation::toIGMASStationInBuffer()
{
    iGMASStationInBuffer bufferItem;
    qMemSet(&bufferItem, 0, sizeof(iGMASStationInBuffer));
    bufferItem.memID = memID;
    bufferItem.isAvailable = true;
    qMemCopy(bufferItem.stationName, stationName.toStdString().c_str(), stationName.length());
    qMemCopy(bufferItem.mountPoint, mountPoint.toStdString().c_str(), mountPoint.length());
    bufferItem.longitude = longitude;
    bufferItem.latitude = latitude;
    bufferItem.height = height;
    qMemCopy(bufferItem.stationDetail, detail.toStdString().c_str(), detail.length());
    qMemCopy(bufferItem.dataCenters, dataCenters.toStdString().c_str(), dataCenters.length());
    return bufferItem;
}
