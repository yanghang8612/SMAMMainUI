#include "standard_station.h"

StandardStation::StandardStation()
{

}

CasterMode::Value StandardStation::getMode() const
{
    return mode;
}

void StandardStation::setMode(const CasterMode::Value& value)
{
	mode = value;
}

void StandardStation::setMode(const QString& value)
{
	if (value.toInt() == 0) {
		mode = CasterMode::IMMEDIATE_CASTER;
	}
	else if (value.toInt() == 1) {
		mode = CasterMode::PROCESS_CASTER;
	}
}

quint8 StandardStation::getServiceThreadCount() const
{
    return serviceThreadCount;
}

void StandardStation::setServiceThreadCount(const quint8& value)
{
	serviceThreadCount = value;
}

void StandardStation::setServiceThreadCount(const QString& value)
{
	serviceThreadCount = value.toUShort();
}

void StandardStation::addReceiver(Receiver* receiver)
{
    receivers << receiver;
}

void StandardStation::removerReceiver(quint8 index)
{
    receivers.removeAt(index);
}

QList<Receiver *> StandardStation::getReceivers() const
{
    return receivers;
}

StandardStationInBuffer StandardStation::toStandardStationInBuffer()
{
    StandardStationInBuffer standardStationInBuffer;
    standardStationInBuffer.stationName = stationName;
    standardStationInBuffer.ipAddress = ipAddress;
    standardStationInBuffer.port = port;
    standardStationInBuffer.deploymentType = (quint8) type;
    standardStationInBuffer.detail = detail;
    standardStationInBuffer.casterMode = (quint8) mode;
    standardStationInBuffer.serviceThreadCount = serviceThreadCount;
    foreach (Receiver* receiver, receivers) {
        standardStationInBuffer.receivers << receiver->toReceiverInBuffer();
    }
    return standardStationInBuffer;
}





