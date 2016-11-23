#ifndef STANDARDSTATION_H
#define STANDARDSTATION_H

#include "base_station.h"
#include "receiver.h"
#include "common.h"

class StandardStation : public BaseStation
{
public:
	StandardStation();

	CasterMode::Value getMode() const;
	void setMode(const CasterMode::Value& value);
	void setMode(const QString& value);

	quint8 getServiceThreadCount() const;
	void setServiceThreadCount(const quint8& value);
	void setServiceThreadCount(const QString& value);

	void addReceiver(Receiver* receiver);

	QList<Receiver*> getReceivers() const;

private:
	CasterMode::Value mode;
	quint8 serviceThreadCount;
	QList<Receiver*> receivers;
};

#endif // STANDARDSTATION_H
