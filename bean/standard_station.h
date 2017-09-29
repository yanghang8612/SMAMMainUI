#ifndef STANDARDSTATION_H
#define STANDARDSTATION_H

#include <QList>

#include "common.h"
#include "smam_component_header.h"
#include "receiver.h"

class StandardStation
{
public:
	StandardStation();

    QString getStationName() const;
    void setStationName(const QString& value);

    DeploymentType::Value getType() const;
    void setType(const DeploymentType::Value& value);
    void setType(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

	void addReceiver(Receiver* receiver);
    void removerReceiver(quint8 index);
    QList<Receiver*> getReceivers() const;

    StandardStationInBuffer toStandardStationInBuffer();

private:
    QString stationName;
    DeploymentType::Value type;
    QString detail;
	QList<Receiver*> receivers;
};

#endif // STANDARDSTATION_H
