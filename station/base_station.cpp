#include "base_station.h"

BaseStation::BaseStation()
{

}

QString BaseStation::getStationName() const
{
	return stationName;
}

void BaseStation::setStationName(const QString& value)
{
	stationName = value;
}

QString BaseStation::getDetail() const
{
    return detail;
}

void BaseStation::setDetail(const QString& value)
{
    detail = value;
}

QString BaseStation::getIpAddress() const
{
    return ipAddress;
}

void BaseStation::setIpAddress(const QString& value)
{
	ipAddress = value;
}

quint16 BaseStation::getPort() const
{
    return port;
}

void BaseStation::setPort(const quint16& value)
{
	port = value;
}

void BaseStation::setPort(const QString& value)
{
	port = value.toUInt();
}

DeploymentType::Value BaseStation::getType() const
{
    return type;
}

void BaseStation::setType(const DeploymentType::Value& value)
{
	type = value;
}

void BaseStation::setType(const QString& value)
{
	if (value.toInt() == 0) {
		type = DeploymentType::XJ_CENTER;
	}
	else if (value.toInt() == 1) {
		type = DeploymentType::BJ_CENTER;
	}
}


