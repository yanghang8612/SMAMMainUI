#include "receiver.h"
#include "common.h"

extern void* receiverSharedBufferPointer;

Receiver::Receiver() : memID(0)
{
    ReceiverInBuffer* item = (ReceiverInBuffer*)((char*)receiverSharedBufferPointer + 4);
    for (int i = 0; i < RECEIVER_MAXITEMCOUNT; i++) {
        if (item->memID == 0) {
            bufferItem = item;
            break;
        }
    }
    (*((int*)receiverSharedBufferPointer))++;
}

Receiver::~Receiver()
{
    (*((int*)receiverSharedBufferPointer))--;
}

int Receiver::getMemID() const
{
    return memID;
}

void Receiver::setMemID(int value)
{
    memID = value;
    bufferItem->memID = value;
}

void Receiver::setMemID(const QString &value)
{
    setMemID(value.toInt());
}

QString Receiver::getReceiverName() const
{
	return receiverName;
}

void Receiver::setReceiverName(const QString& value)
{
	receiverName = value;
    qMemSet(bufferItem->receiverName, 0, sizeof(bufferItem->receiverName));
    qMemCopy(bufferItem->receiverName, value.toStdString().c_str(), value.length());
}

QString Receiver::getPassword() const
{
    return password;
}

void Receiver::setPassword(const QString& value)
{
    password = value;
    qMemSet(bufferItem->password, 0, sizeof(bufferItem->password));
    qMemCopy(bufferItem->password, value.toStdString().c_str(), value.length());
}

QString Receiver::getIpAddress() const
{
    return ipAddress;
}

void Receiver::setIpAddress(const QString& value)
{
    ipAddress = value;
    qMemSet(bufferItem->ipAddress, 0, sizeof(bufferItem->ipAddress));
    qMemCopy(bufferItem->ipAddress, value.toStdString().c_str(), value.length());
}

quint16 Receiver::getPort() const
{
    return port;
}

void Receiver::setPort(const quint16& value)
{
	port = value;
    bufferItem->port = value;
}

void Receiver::setPort(const QString& value)
{
    setPort(value.toUShort());
}

QString Receiver::getMountPoint() const
{
    return mountPoint;
}

void Receiver::setMountPoint(const QString& value)
{
    mountPoint = value;
    qMemSet(bufferItem->mountPoint, 0, sizeof(bufferItem->mountPoint));
    qMemCopy(bufferItem->mountPoint, ("/" + value).toStdString().c_str(), ("/" + value).length());
}

float Receiver::getLongitude() const
{
    return longitude;
}

void Receiver::setLongitude(float value)
{
	longitude = value;
    bufferItem->longitude = value;
}

void Receiver::setLongitude(const QString& value)
{
    setLongitude(value.toFloat());
}

float Receiver::getLatitude() const
{
    return latitude;
}

void Receiver::setLatitude(float value)
{
	latitude = value;
    bufferItem->latitude = value;
}

void Receiver::setLatitude(const QString& value)
{
    setLatitude(value.toFloat());
}

float Receiver::getHeight() const
{
    return height;
}

void Receiver::setHeight(float value)
{
    height = value;
    bufferItem->height = value;
}

void Receiver::setHeight(const QString& value)
{
    setHeight(value.toFloat());
}

QString Receiver::getDetail() const
{
    return receiverDetail;
}

void Receiver::setDetail(const QString& value)
{
    receiverDetail = value;
    qMemSet(bufferItem->receiverDetail, 0, sizeof(bufferItem->receiverDetail));
    qMemCopy(bufferItem->receiverDetail, value.toStdString().c_str(), value.length());
}

ReceiverInBuffer*Receiver::getBufferItem()
{
    return bufferItem;
}

ReceiverInBuffer Receiver::toReceiverInBuffer()
{
    ReceiverInBuffer bufferItem;
    qMemSet(&bufferItem, 0, sizeof(ReceiverInBuffer));
    bufferItem.memID = memID;
    qMemCopy(bufferItem.receiverName, receiverName.toStdString().c_str(), receiverName.length());
    qMemCopy(bufferItem.password, password.toStdString().c_str(), password.length());
    qMemCopy(bufferItem.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    bufferItem.port = port;
    qMemCopy(bufferItem.mountPoint, ("/" + mountPoint).toStdString().c_str(), mountPoint.length() + 1);
    bufferItem.longitude = longitude;
    bufferItem.latitude = latitude;
    bufferItem.height = height;
    qMemCopy(bufferItem.receiverDetail, receiverDetail.toStdString().c_str(), receiverDetail.length());
    return bufferItem;
}













