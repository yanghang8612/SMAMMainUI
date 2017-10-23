#include "other_center.h"
#include "common.h"

extern void* otherCenterSharedBufferPointer;

OtherCenter::OtherCenter() : centerID(0)
{
    OtherCenterInBuffer* item = (OtherCenterInBuffer*)((char*)otherCenterSharedBufferPointer + 4);
    for (int i = 0; i < OTHERCENTER_MAXITEMCOUNT; i++, item++) {
        if (item->centerID == 0) {
            bufferItem = item;
            break;
        }
    }
    (*((int*)otherCenterSharedBufferPointer))++;
}

OtherCenter::~OtherCenter()
{
    bufferItem->centerID = 0;
    (*((int*)otherCenterSharedBufferPointer))--;
}

qint32 OtherCenter::getCenterID() const
{
    return centerID;
}

void OtherCenter::setCenterID(const qint32& value)
{
    centerID = value;
    bufferItem->centerID = value;
}

void OtherCenter::setCenterID(const QString& value)
{
    setCenterID(value.toInt());
}

QString OtherCenter::getCenterName() const
{
    return centerName;
}

void OtherCenter::setCenterName(const QString& value)
{
    centerName = value;
    qMemSet(bufferItem->centerName, 0, sizeof(bufferItem->centerName));
    qMemCopy(bufferItem->centerName, value.toStdString().c_str(), value.length());
}

QString OtherCenter::getIpAddress() const
{
    return ipAddress;
}

void OtherCenter::setIpAddress(const QString& value)
{
    ipAddress = value;
    qMemSet(bufferItem->ipAddress, 0, sizeof(bufferItem->ipAddress));
    qMemCopy(bufferItem->ipAddress, value.toStdString().c_str(), value.length());
}

QString OtherCenter::getUsername() const
{
    return username;
}

void OtherCenter::setUsername(const QString& value)
{
    username = value;
    qMemSet(bufferItem->username, 0, sizeof(bufferItem->username));
    qMemCopy(bufferItem->username, value.toStdString().c_str(), value.length());
}

QString OtherCenter::getPassword() const
{
    return password;
}

void OtherCenter::setPassword(const QString& value)
{
    password = value;
    qMemSet(bufferItem->password, 0, sizeof(bufferItem->password));
    qMemCopy(bufferItem->password, value.toStdString().c_str(), value.length());
}

QString OtherCenter::getDetail() const
{
    return centerDetail;
}

void OtherCenter::setDetail(const QString& value)
{
    centerDetail = value;
    qMemSet(bufferItem->centerDetail, 0, sizeof(bufferItem->centerDetail));
    qMemCopy(bufferItem->centerDetail, value.toStdString().c_str(), value.length());
}

OtherCenterInBuffer*OtherCenter::getBufferItem()
{
    return bufferItem;
}

OtherCenterInBuffer OtherCenter::toOtherCenterInBuffer()
{
    OtherCenterInBuffer bufferItem;
    qMemSet(&bufferItem, 0, sizeof(OtherCenterInBuffer));
    bufferItem.centerID = centerID;
    qMemCopy(bufferItem.centerName, centerName.toStdString().c_str(), centerName.length());
    qMemCopy(bufferItem.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    qMemCopy(bufferItem.username, username.toStdString().c_str(), username.length());
    qMemCopy(bufferItem.password, password.toStdString().c_str(), password.length());
    qMemCopy(bufferItem.centerDetail, centerDetail.toStdString().c_str(), centerDetail.length());
    return bufferItem;
}





