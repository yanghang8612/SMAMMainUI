#include "base_center.h"

BaseCenter::BaseCenter()
{

}
QString BaseCenter::getCenterName() const
{
    return centerName;
}

void BaseCenter::setCenterName(const QString& value)
{
    centerName = value;
}

QString BaseCenter::getIpAddress() const
{
    return ipAddress;
}

void BaseCenter::setIpAddress(const QString& value)
{
    ipAddress = value;
}

quint16 BaseCenter::getPort() const
{
    return port;
}

void BaseCenter::setPort(const quint16& value)
{
    port = value;
}

void BaseCenter::setPort(const QString& value)
{
    port = value.toUInt();
}

QString BaseCenter::getDetail() const
{
    return detail;
}

void BaseCenter::setDetail(const QString& value)
{
    detail = value;
}





