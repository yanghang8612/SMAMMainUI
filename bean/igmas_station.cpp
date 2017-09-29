#include "igmas_station.h"

iGMASStation::iGMASStation()
{
    this->memID = -1;
}

QString iGMASStation::getStationName() const
{
    return stationName;
}

void iGMASStation::setStationName(const QString& value)
{
    stationName = value;
}

QString iGMASStation::getMountPoint() const
{
    return mountPoint;
}

void iGMASStation::setMountPoint(const QString& value)
{
    mountPoint = value;
}

int iGMASStation::getMemID() const
{
    return memID;
}

void iGMASStation::setMemID(int value)
{
    memID = value;
}

void iGMASStation::setMemID(const QString& value)
{
    memID = value.toInt();
}

double iGMASStation::getLongitude() const
{
    return longitude;
}

void iGMASStation::setLongitude(double value)
{
    longitude = value;
}

void iGMASStation::setLongitude(const QString& value)
{
    longitude = value.toDouble();
}

double iGMASStation::getLatitude() const
{
    return latitude;
}

void iGMASStation::setLatitude(double value)
{
    latitude = value;
}

void iGMASStation::setLatitude(const QString& value)
{
    latitude = value.toDouble();
}

double iGMASStation::getHeight() const
{
    return height;
}

void iGMASStation::setHeight(double value)
{
    height = value;
}

void iGMASStation::setHeight(const QString& value)
{
    height = value.toDouble();
}

QString iGMASStation::getDetail() const
{
    return detail;
}

void iGMASStation::setDetail(const QString& value)
{
    detail = value;
}

iGMASStationInBuffer iGMASStation::toIGMASStationInBuffer()
{
    iGMASStationInBuffer bufferItem;
    qMemSet(&bufferItem, 0, sizeof(iGMASStationInBuffer));
    bufferItem.isAvailable = true;
    qMemCopy(bufferItem.stationName, stationName.toStdString().c_str(), stationName.length());
    qMemCopy(bufferItem.mountPoint, mountPoint.toStdString().c_str(), mountPoint.length());
    bufferItem.memID = memID;
    bufferItem.longitude = longitude;
    bufferItem.latitude = latitude;
    bufferItem.height = height;
    qMemCopy(bufferItem.detail, detail.toStdString().c_str(), detail.length());
    return bufferItem;
}











