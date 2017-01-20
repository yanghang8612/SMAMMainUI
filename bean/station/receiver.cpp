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

ReceiverInBuffer Receiver::toReceiverInBuffer()
{
    ReceiverInBuffer receiverInBuffer;
    receiverInBuffer.receiverName = receiverName;
    receiverInBuffer.ipAddress = ipAddress;
    receiverInBuffer.port = port;
    receiverInBuffer.longitude = longitude;
    receiverInBuffer.latitude = latitude;
    return receiverInBuffer;
}






