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
    setCenterID(0);
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
    qstrcpy(bufferItem->centerName, value.toStdString().c_str());
}

QString OtherCenter::getIpAddress() const
{
    return ipAddress;
}

void OtherCenter::setIpAddress(const QString& value)
{
    ipAddress = value;
    qstrcpy(bufferItem->ipAddress, value.toStdString().c_str());
}

QString OtherCenter::getUsername() const
{
    return username;
}

void OtherCenter::setUsername(const QString& value)
{
    username = value;
    qstrcpy(bufferItem->username, value.toStdString().c_str());
}

QString OtherCenter::getPassword() const
{
    return password;
}

void OtherCenter::setPassword(const QString& value)
{
    password = value;
    qstrcpy(bufferItem->password, value.toStdString().c_str());
}

QString OtherCenter::getDetail() const
{
    return centerDetail;
}

void OtherCenter::setDetail(const QString& value)
{
    centerDetail = value;
    qstrcpy(bufferItem->centerDetail, value.toStdString().c_str());
}

OtherCenterInBuffer*OtherCenter::getBufferItem()
{
    return bufferItem;
}

OtherCenterInBuffer OtherCenter::toOtherCenterInBuffer()
{
    OtherCenterInBuffer bufferItem;
    bufferItem.centerID = centerID;
    qstrcpy(bufferItem.centerName, centerName.toStdString().c_str());
    qstrcpy(bufferItem.ipAddress, ipAddress.toStdString().c_str());
    qstrcpy(bufferItem.username, username.toStdString().c_str());
    qstrcpy(bufferItem.password, password.toStdString().c_str());
    qstrcpy(bufferItem.centerDetail, centerDetail.toStdString().c_str());
    return bufferItem;
}





