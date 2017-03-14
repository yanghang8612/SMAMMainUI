#include "receiver.h"

Receiver::Receiver()
{

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

ReceiverInBuffer Receiver::toReceiverInBuffer()
{
    ReceiverInBuffer receiverInBuffer;
    qMemSet(&receiverInBuffer, 0, sizeof(ReceiverInBuffer));
    qMemCopy(receiverInBuffer.receiverName, receiverName.toStdString().c_str(), receiverName.length());
    qMemCopy(receiverInBuffer.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    receiverInBuffer.port = port;
    receiverInBuffer.longitude = longitude;
    receiverInBuffer.latitude = latitude;
    receiverInBuffer.height = height;
    qMemCopy(receiverInBuffer.detail, detail.toStdString().c_str(), detail.length());
    return receiverInBuffer;
}











