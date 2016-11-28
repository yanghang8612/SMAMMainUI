#ifndef BASESTATION_H
#define BASESTATION_H

#include "common.h"

class BaseStation
{
public:
	BaseStation();

	//Getter and Setter function
	QString getStationName() const;
	void setStationName(const QString& value);

	QString getDetail() const;
	void setDetail(const QString& value);

	QString getIpAddress() const;
	void setIpAddress(const QString& value);

	quint16 getPort() const;
	void setPort(const quint16& value);
	void setPort(const QString& value);

	DeploymentType::Value getType() const;
	void setType(const DeploymentType::Value& value);
	void setType(const QString& value);

protected:
	QString stationName;
	QString detail;
	QString ipAddress;
	quint16 port;
	DeploymentType::Value type;
};

#endif // BASESTATION_H
