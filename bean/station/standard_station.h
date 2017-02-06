#ifndef STANDARDSTATION_H
#define STANDARDSTATION_H

#include <QList>

#include "base_station.h"
#include "receiver.h"
#include "common.h"
#include "smam_component_header.h"

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
    void removerReceiver(quint8 index);
    QList<Receiver*> getReceivers() const;

    StandardStationInBuffer toStandardStationInBuffer();

private:
    CasterMode::Value mode;
    quint8 serviceThreadCount;
	QList<Receiver*> receivers;
};

#endif // STANDARDSTATION_H
