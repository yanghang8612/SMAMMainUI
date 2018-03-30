#include "data_center.h"
#include "common.h"

extern void* dataCenterSharedBufferPointer;

DataCenter::DataCenter() : centerID(0)
{
    DataCenterInBuffer* item = (DataCenterInBuffer*)((char*)dataCenterSharedBufferPointer + 4);
    for (int i = 0; i < DATACENTER_MAXITEMCOUNT; i++, item++) {
        if (item->centerID == 0) {
            bufferItem = item;
            break;
        }
    }
    (*((int*)dataCenterSharedBufferPointer))++;
}

DataCenter::~DataCenter()
{
    setCenterID(0);
    (*((int*)dataCenterSharedBufferPointer))--;
}

qint32 DataCenter::getCenterID() const
{
    return centerID;
}

void DataCenter::setCenterID(const qint32& value)
{
    centerID = value;
    bufferItem->centerID = value;
}

void DataCenter::setCenterID(const QString& value)
{
    setCenterID(value.toInt());
}

QString DataCenter::getCenterName() const
{
    return centerName;
}

void DataCenter::setCenterName(const QString& value)
{
    centerName = value;
    qstrcpy(bufferItem->centerName, value.toStdString().c_str());
}

QString DataCenter::getMasterIPAddress() const
{
    return masterIPAddress;
}

void DataCenter::setMasterIPAddress(const QString& value)
{
    masterIPAddress = value;
    qstrcpy(bufferItem->masterIPAddress, value.toStdString().c_str());
}

quint16 DataCenter::getMasterPort() const
{
    return masterPort;
}

void DataCenter::setMasterPort(const quint16& value)
{
    masterPort = value;
    bufferItem->masterPort = value;
}

void DataCenter::setMasterPort(const QString& value)
{
    setMasterPort(value.toUShort());
}

QString DataCenter::getSlaveIPAddress() const
{
    return slaveIPAddress;
}

void DataCenter::setSlaveIPAddress(const QString& value)
{
    slaveIPAddress = value;
    qstrcpy(bufferItem->slaveIPAddress, value.toStdString().c_str());
}

quint16 DataCenter::getSlavePort() const
{
    return slavePort;
}

void DataCenter::setSlavePort(const quint16& value)
{
    slavePort = value;
    bufferItem->slavePort = value;
}

void DataCenter::setSlavePort(const QString& value)
{
    setSlavePort(value.toInt());
}

QString DataCenter::getUsername() const
{
    return username;
}

void DataCenter::setUsername(const QString& value)
{
    username = value;
    qstrcpy(bufferItem->username, value.toStdString().c_str());
}

QString DataCenter::getPassword() const
{
    return password;
}

void DataCenter::setPassword(const QString& value)
{
    password = value;
    qstrcpy(bufferItem->password, value.toStdString().c_str());
}

QString DataCenter::getCenterDetail() const
{
    return centerDetail;
}

void DataCenter::setCenterDetail(const QString& value)
{
    centerDetail = value;
    qstrcpy(bufferItem->centerDetail, value.toStdString().c_str());
}

DataCenterInBuffer*DataCenter::getBufferItem()
{
    return bufferItem;
}

DataCenterInBuffer DataCenter::toDataCenterInBuffer()
{
    DataCenterInBuffer bufferItem;
    bufferItem.centerID = centerID;
    qstrcpy(bufferItem.centerName, centerName.toStdString().c_str());
    qstrcpy(bufferItem.masterIPAddress, masterIPAddress.toStdString().c_str());
    bufferItem.masterPort = masterPort;
    qstrcpy(bufferItem.slaveIPAddress, slaveIPAddress.toStdString().c_str());
    bufferItem.slavePort = slavePort;
    qstrcpy(bufferItem.username, username.toStdString().c_str());
    qstrcpy(bufferItem.password, password.toStdString().c_str());
    qstrcpy(bufferItem.centerDetail, centerDetail.toStdString().c_str());
    return bufferItem;
}

