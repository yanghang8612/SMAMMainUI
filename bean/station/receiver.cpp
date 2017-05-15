#include "receiver.h"

Receiver::Receiver()
{}

int Receiver::getMemID() const
{
    return memID;
}

void Receiver::setMemID(int value)
{
    memID = value;
}

void Receiver::setMemID(const QString &value)
{
    memID = value.toInt();
}

QString Receiver::getReceiverName() const
{
	return receiverName;
}

void Receiver::setReceiverName(const QString& value)
{
	receiverName = value;
}

QString Receiver::getPassword() const
{
    return password;
}

void Receiver::setPassword(const QString& value)
{
    password = value;
}

QString Receiver::getIpAddress() const
{
    return ipAddress;
}

void Receiver::setIpAddress(const QString& value)
{
    ipAddress = value;
}

quint16 Receiver::getPort() const
{
    return port;
}

void Receiver::setPort(const quint16& value)
{
	port = value;
}

void Receiver::setPort(const QString& value)
{
	port = value.toUInt();
}

float Receiver::getLongitude() const
{
    return longitude;
}

void Receiver::setLongitude(float value)
{
	longitude = value;
}

void Receiver::setLongitude(const QString& value)
{
	longitude = value.toFloat();
}

float Receiver::getLatitude() const
{
    return latitude;
}

void Receiver::setLatitude(float value)
{
	latitude = value;
}

void Receiver::setLatitude(const QString& value)
{
    latitude = value.toFloat();
}

float Receiver::getHeight() const
{
    return height;
}

void Receiver::setHeight(float value)
{
    height = value;
}

void Receiver::setHeight(const QString& value)
{
    height = value.toFloat();
}

QString Receiver::getDetail() const
{
    return detail;
}

void Receiver::setDetail(const QString& value)
{
    detail = value;
}

QString Receiver::getMount() const
{
    return mount;
}

void Receiver::setMount(const QString& value)
{
    mount = value;
}

ReceiverInBuffer Receiver::toReceiverInBuffer()
{
    ReceiverInBuffer receiverInBuffer;
    qMemSet(&receiverInBuffer, 0, sizeof(ReceiverInBuffer));
    receiverInBuffer.memID = memID;
    qMemCopy(receiverInBuffer.receiverName, receiverName.toStdString().c_str(), receiverName.length());
    qMemCopy(receiverInBuffer.password, password.toStdString().c_str(), password.length());
    qMemCopy(receiverInBuffer.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    receiverInBuffer.port = port;
    receiverInBuffer.longitude = longitude;
    receiverInBuffer.latitude = latitude;
    receiverInBuffer.height = height;
    qMemCopy(receiverInBuffer.detail, detail.toStdString().c_str(), detail.length());
    qMemCopy(receiverInBuffer.mount, ("/" + mount).toStdString().c_str(), mount.length() + 1);
    return receiverInBuffer;
}













