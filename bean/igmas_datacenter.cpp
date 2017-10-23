#include "igmas_datacenter.h"
#include "common.h"

extern void* iGMASDataCenterSharedBufferPointer;

iGMASDataCenter::iGMASDataCenter() : centerID(0)
{
    iGMASDataCenterInBuffer* item = (iGMASDataCenterInBuffer*)((char*)iGMASDataCenterSharedBufferPointer + 4);
    for (int i = 0; i < IGMASDATACENTER_MAXITEMCOUNT; i++, item++) {
        if (item->centerID == 0) {
            bufferItem = item;
            break;
        }
    }
    (*((int*)iGMASDataCenterSharedBufferPointer))++;
}

iGMASDataCenter::~iGMASDataCenter()
{
    bufferItem->centerID = 0;
    (*((int*)iGMASDataCenterSharedBufferPointer))--;
}

qint32 iGMASDataCenter::getCenterID() const
{
    return centerID;
}

void iGMASDataCenter::setCenterID(const qint32& value)
{
    centerID = value;
    bufferItem->centerID = value;
}

void iGMASDataCenter::setCenterID(const QString& value)
{
    setCenterID(value.toInt());
}

QString iGMASDataCenter::getCenterName() const
{
    return centerName;
}

void iGMASDataCenter::setCenterName(const QString& value)
{
    centerName = value;
    qMemSet(bufferItem->centerName, 0, sizeof(bufferItem->centerName));
    qMemCopy(bufferItem->centerName, value.toStdString().c_str(), value.length());
}

QString iGMASDataCenter::getMasterIPAddress() const
{
    return masterIPAddress;
}

void iGMASDataCenter::setMasterIPAddress(const QString& value)
{
    masterIPAddress = value;
    qMemSet(bufferItem->masterIPAddress, 0, sizeof(bufferItem->masterIPAddress));
    qMemCopy(bufferItem->masterIPAddress, value.toStdString().c_str(), value.length());
}

quint16 iGMASDataCenter::getMasterPort() const
{
    return masterPort;
}

void iGMASDataCenter::setMasterPort(const quint16& value)
{
    masterPort = value;
    bufferItem->masterPort = value;
}

void iGMASDataCenter::setMasterPort(const QString& value)
{
    setMasterPort(value.toUShort());
}

QString iGMASDataCenter::getSlaveIPAddress() const
{
    return slaveIPAddress;
}

void iGMASDataCenter::setSlaveIPAddress(const QString& value)
{
    slaveIPAddress = value;
    qMemSet(bufferItem->slaveIPAddress, 0, sizeof(bufferItem->slaveIPAddress));
    qMemCopy(bufferItem->slaveIPAddress, value.toStdString().c_str(), value.length());
}

quint16 iGMASDataCenter::getSlavePort() const
{
    return slavePort;
}

void iGMASDataCenter::setSlavePort(const quint16& value)
{
    slavePort = value;
    bufferItem->slavePort = value;
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
    qMemSet(bufferItem->username, 0, sizeof(bufferItem->username));
    qMemCopy(bufferItem->username, value.toStdString().c_str(), value.length());
}

QString iGMASDataCenter::getPassword() const
{
    return password;
}

void iGMASDataCenter::setPassword(const QString& value)
{
    password = value;
    qMemSet(bufferItem->password, 0, sizeof(bufferItem->password));
    qMemCopy(bufferItem->password, value.toStdString().c_str(), value.length());
}

QString iGMASDataCenter::getCenterDetail() const
{
    return centerDetail;
}

void iGMASDataCenter::setCenterDetail(const QString& value)
{
    centerDetail = value;
    qMemSet(bufferItem->centerDetail, 0, sizeof(bufferItem->centerDetail));
    qMemCopy(bufferItem->centerDetail, value.toStdString().c_str(), value.length());
}

iGMASDataCenterInBuffer*iGMASDataCenter::getBufferItem()
{
    return bufferItem;
}

iGMASDataCenterInBuffer iGMASDataCenter::toIGMASDataCenterInBuffer()
{
    iGMASDataCenterInBuffer bufferItem;
    qMemSet(&bufferItem, 0, sizeof(iGMASDataCenterInBuffer));
    bufferItem.centerID = centerID;
    qMemCopy(bufferItem.centerName, centerName.toStdString().c_str(), centerName.length());
    qMemCopy(bufferItem.masterIPAddress, masterIPAddress.toStdString().c_str(), masterIPAddress.length());
    bufferItem.masterPort = masterPort;
    qMemCopy(bufferItem.slaveIPAddress, slaveIPAddress.toStdString().c_str(), slaveIPAddress.length());
    bufferItem.slavePort = slavePort;
    qMemCopy(bufferItem.username, username.toStdString().c_str(), username.length());
    qMemCopy(bufferItem.password, password.toStdString().c_str(), password.length());
    qMemCopy(bufferItem.centerDetail, centerDetail.toStdString().c_str(), centerDetail.length());
    return bufferItem;
}

