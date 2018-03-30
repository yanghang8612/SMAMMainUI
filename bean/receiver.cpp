#include "receiver.h"
#include "common.h"
#include "utilities/general_functions.h"

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
    setMemID(0);
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
    qstrcpy(bufferItem->receiverName, value.toStdString().c_str());
}

QString Receiver::getPassword() const
{
    return password;
}

void Receiver::setPassword(const QString& value)
{
    password = value;
    qstrcpy(bufferItem->password, value.toStdString().c_str());
}

QString Receiver::getIpAddress() const
{
    return ipAddress;
}

void Receiver::setIpAddress(const QString& value)
{
    ipAddress = value;
    qstrcpy(bufferItem->ipAddress, value.toStdString().c_str());
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
    qstrcpy(bufferItem->mountPoint, ("/" + value).toStdString().c_str());
}

DMS Receiver::getLongitude() const
{
    return longitude;
}

void Receiver::setLongitude(const DMS& value)
{
    longitude = value;
}

void Receiver::setLongitude(const QString& value)
{
    setLongitude(GeneralFunctions::convertQStringToDMS(value));
}

DMS Receiver::getLatitude() const
{
    return latitude;
}

void Receiver::setLatitude(const DMS& value)
{
    latitude = value;
}

void Receiver::setLatitude(const QString& value)
{
    setLatitude(GeneralFunctions::convertQStringToDMS(value));
}

double Receiver::getHeight() const
{
    return height;
}

void Receiver::setHeight(double value)
{
    height = value;
}

void Receiver::setHeight(const QString& value)
{
    setHeight(value.toDouble());
}

QString Receiver::getDetail() const
{
    return receiverDetail;
}

void Receiver::setDetail(const QString& value)
{
    receiverDetail = value;
    qstrcpy(bufferItem->receiverDetail, value.toStdString().c_str());
}

ReceiverInBuffer*Receiver::getBufferItem()
{
    return bufferItem;
}

ReceiverInBuffer Receiver::toReceiverInBuffer()
{
    ReceiverInBuffer bufferItem;
    bufferItem.memID = memID;
    qstrcpy(bufferItem.receiverName, receiverName.toStdString().c_str());
    qstrcpy(bufferItem.password, password.toStdString().c_str());
    qstrcpy(bufferItem.ipAddress, ipAddress.toStdString().c_str());
    bufferItem.port = port;
    qstrcpy(bufferItem.mountPoint, ("/" + mountPoint).toStdString().c_str());
    bufferItem.longitude = longitude;
    bufferItem.latitude = latitude;
    bufferItem.height = height;
    qstrcpy(bufferItem.receiverDetail, receiverDetail.toStdString().c_str());
    return bufferItem;
}
