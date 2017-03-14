#include "igmas_station.h"

IGMASStation::IGMASStation()
{

}

bool IGMASStation::getIsAvailable() const
{
    return isAvailable;
}

void IGMASStation::setIsAvailable(bool value)
{
    isAvailable = value;
}

void IGMASStation::setIsAvailable(const QString& value)
{
    isAvailable = (value.toInt() == 1) ? true : false;
}

void IGMASStation::setIsAvailable(int value)
{
    isAvailable = (value == 1) ? true : false;
}

QString IGMASStation::getMount() const
{
    return mount;
}

void IGMASStation::setMount(const QString& value)
{
    mount = value;
}

int IGMASStation::getMemID() const
{
    return memID;
}

void IGMASStation::setMemID(int value)
{
    memID = value;
}

void IGMASStation::setMemID(const QString& value)
{
    memID = value.toInt();
}

double IGMASStation::getLongitude() const
{
    return longitude;
}

void IGMASStation::setLongitude(double value)
{
    longitude = value;
}

void IGMASStation::setLongitude(const QString& value)
{
    longitude = value.toDouble();
}

double IGMASStation::getLatitude() const
{
    return latitude;
}

void IGMASStation::setLatitude(double value)
{
    latitude = value;
}

void IGMASStation::setLatitude(const QString& value)
{
    latitude = value.toDouble();
}

double IGMASStation::getHeight() const
{
    return height;
}

void IGMASStation::setHeight(double value)
{
    height = value;
}

void IGMASStation::setHeight(const QString& value)
{
    height = value.toDouble();
}

IGMASStationInBuffer IGMASStation::toiGMASStationInBuffer()
{
    IGMASStationInBuffer iGMASStationInBuffer;
    qMemSet(&iGMASStationInBuffer, 0, sizeof(IGMASStationInBuffer));
    iGMASStationInBuffer.isAvailable = isAvailable;
    qMemSet(iGMASStationInBuffer.ipAddress, 0, sizeof(iGMASStationInBuffer.ipAddress));
    qMemCopy(iGMASStationInBuffer.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    iGMASStationInBuffer.port = port;
    qMemCopy(iGMASStationInBuffer.mount, mount.toStdString().c_str(), mount.length());
    iGMASStationInBuffer.memID = memID;
    iGMASStationInBuffer.longitude = longitude;
    iGMASStationInBuffer.latitude = latitude;
    iGMASStationInBuffer.height = height;
    return iGMASStationInBuffer;
}







