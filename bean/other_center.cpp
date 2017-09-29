#include "other_center.h"

OtherCenter::OtherCenter()
{}

QString OtherCenter::getCenterName() const
{
    return centerName;
}

void OtherCenter::setCenterName(const QString& value)
{
    centerName = value;
}

QString OtherCenter::getIpAddress() const
{
    return ipAddress;
}

void OtherCenter::setIpAddress(const QString& value)
{
    ipAddress = value;
}

quint16 OtherCenter::getPort() const
{
    return port;
}

void OtherCenter::setPort(const quint16& value)
{
    port = value;
}

void OtherCenter::setPort(const QString& value)
{
    port = value.toInt();
}

QString OtherCenter::getUsername() const
{
    return username;
}

void OtherCenter::setUsername(const QString& value)
{
    username = value;
}

QString OtherCenter::getPassword() const
{
    return password;
}

void OtherCenter::setPassword(const QString& value)
{
    password = value;
}

QString OtherCenter::getDetail() const
{
    return detail;
}

void OtherCenter::setDetail(const QString& value)
{
    detail = value;
}

OtherCenterInBuffer OtherCenter::toOtherCenterInBuffer()
{
    OtherCenterInBuffer bufferItem;
    qMemSet(&bufferItem, 0, sizeof(OtherCenterInBuffer));
    qMemCopy(bufferItem.centerName, centerName.toStdString().c_str(), centerName.length());
    qMemCopy(bufferItem.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    bufferItem.port = port;
    qMemCopy(bufferItem.username, username.toStdString().c_str(), username.length());
    qMemCopy(bufferItem.password, password.toStdString().c_str(), password.length());
    qMemCopy(bufferItem.detail, detail.toStdString().c_str(), detail.length());
    qMemCopy(bufferItem.mountPoint, "/RTA02", qstrlen("/RTA02"));
    return bufferItem;
}



