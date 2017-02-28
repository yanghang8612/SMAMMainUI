#include "standard_station.h"

StandardStation::StandardStation()
{

}

QString StandardStation::getStationName() const
{
    return stationName;
}

void StandardStation::setStationName(const QString& value)
{
    stationName = value;
}

DeploymentType::Value StandardStation::getType() const
{
    return type;
}

void StandardStation::setType(const DeploymentType::Value& value)
{
    type = value;
}

void StandardStation::setType(const QString& value)
{
    if (value.toInt() == 0) {
        type = DeploymentType::XJ_CENTER;
    }
    else if (value.toInt() == 1) {
        type = DeploymentType::BJ_CENTER;
    }
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
    qMemCopy(standardStationInBuffer.stationName, stationName.toStdString().c_str(), stationName.length());
    qMemCopy(standardStationInBuffer.detail, detail.toStdString().c_str(), detail.length());
    qMemCopy(standardStationInBuffer.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    standardStationInBuffer.port = port;
    standardStationInBuffer.deploymentType = (quint8) type;
    standardStationInBuffer.casterMode = (quint8) mode;
    standardStationInBuffer.serviceThreadCount = serviceThreadCount;
    standardStationInBuffer.receiverCount = (quint8) receivers.size();
    for (int i = 0; i < receivers.size(); i++) {
        standardStationInBuffer.receivers[i] = receivers[i]->toReceiverInBuffer();
    }
    return standardStationInBuffer;
}





