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
    qMemSet(&standardStationInBuffer, 0, sizeof(StandardStationInBuffer));
    qMemCopy(standardStationInBuffer.stationName, stationName.toStdString().c_str(), stationName.length());
    qMemCopy(standardStationInBuffer.detail, detail.toStdString().c_str(), detail.length());
    standardStationInBuffer.deploymentType = (quint8) type;
    standardStationInBuffer.receiverCount = (quint8) receivers.size();
    for (int i = 0; i < receivers.size(); i++) {
        standardStationInBuffer.receivers[i] = receivers[i]->toReceiverInBuffer();
    }
    return standardStationInBuffer;
}





