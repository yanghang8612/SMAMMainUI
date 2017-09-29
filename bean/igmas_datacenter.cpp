#include <QDebug>

#include "igmas_datacenter.h"

iGMASDataCenter::iGMASDataCenter()
{}

QString iGMASDataCenter::getCenterName() const
{
    return centerName;
}

void iGMASDataCenter::setCenterName(const QString& value)
{
    centerName = value;
}

QString iGMASDataCenter::getMasterIPAddress() const
{
    return masterIPAddress;
}

void iGMASDataCenter::setMasterIPAddress(const QString& value)
{
    masterIPAddress = value;
}

quint16 iGMASDataCenter::getMasterPort() const
{
    return masterPort;
}

void iGMASDataCenter::setMasterPort(const quint16& value)
{
    masterPort = value;
}

void iGMASDataCenter::setMasterPort(const QString& value)
{
    setMasterPort(value.toUInt());
}

QString iGMASDataCenter::getSlaveIPAddress() const
{
    return slaveIPAddress;
}

void iGMASDataCenter::setSlaveIPAddress(const QString& value)
{
    slaveIPAddress = value;
}

quint16 iGMASDataCenter::getSlavePort() const
{
    return slavePort;
}

void iGMASDataCenter::setSlavePort(const quint16& value)
{
    slavePort = value;
}

void iGMASDataCenter::setSlavePort(const QString& value)
{
    setSlavePort(value.toInt());
}

QString iGMASDataCenter::getUsername() const
{
    return username;
}

void iGMASDataCenter::setUsername(const QString& value)
{
    username = value;
}

QString iGMASDataCenter::getPassword() const
{
    return password;
}

void iGMASDataCenter::setPassword(const QString& value)
{
    password = value;
}

QString iGMASDataCenter::getCenterDetail() const
{
    return centerDetail;
}

void iGMASDataCenter::setCenterDetail(const QString& value)
{
    centerDetail = value;
}

iGMASDataCenterInBuffer iGMASDataCenter::toIGMASDataCenterInBuffer()
{
    iGMASDataCenterInBuffer bufferItem;
    qMemSet(&bufferItem, 0, sizeof(iGMASDataCenterInBuffer));
    bufferItem.isAvailable = true;
    qMemCopy(bufferItem.centerName, centerName.toStdString().c_str(), centerName.length());
    qMemCopy(bufferItem.masterIPAddress, masterIPAddress.toStdString().c_str(), masterIPAddress.length());
    bufferItem.masterPort = masterPort;
    qMemCopy(bufferItem.slaveIPAddress, slaveIPAddress.toStdString().c_str(), slaveIPAddress.length());
    bufferItem.slavePort = slavePort;
    qMemCopy(bufferItem.username, username.toStdString().c_str(), username.length());
    qMemCopy(bufferItem.password, password.toStdString().c_str(), password.length());
    qMemCopy(bufferItem.detail, centerDetail.toStdString().c_str(), centerDetail.length());
    return bufferItem;
}
