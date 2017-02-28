#include "base_station.h"

BaseStation::BaseStation()
{

}

QString BaseStation::getIpAddress() const
{
    return ipAddress;
}

void BaseStation::setIpAddress(const QString& value)
{
	ipAddress = value;
}

quint16 BaseStation::getPort() const
{
    return port;
}

void BaseStation::setPort(const quint16& value)
{
	port = value;
}

void BaseStation::setPort(const QString& value)
{
	port = value.toUInt();
}

QString BaseStation::getDetail() const
{
    return detail;
}

void BaseStation::setDetail(const QString& value)
{
    detail = value;
}


