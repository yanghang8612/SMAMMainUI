#ifndef BASESTATION_H
#define BASESTATION_H

#include "common.h"

class BaseStation
{
public:
	BaseStation();

	QString getIpAddress() const;
	void setIpAddress(const QString& value);

	quint16 getPort() const;
	void setPort(const quint16& value);
	void setPort(const QString& value);

protected:
	QString ipAddress;
    quint16 port;
};

#endif // BASESTATION_H
