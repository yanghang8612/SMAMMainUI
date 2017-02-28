#ifndef RECEIVER_H
#define RECEIVER_H

#include <QString>

#include "smam_component_header.h"

class Receiver
{
public:
	Receiver();

	QString getReceiverName() const;
	void setReceiverName(const QString& value);

	QString getIpAddress() const;
	void setIpAddress(const QString& value);

	quint16 getPort() const;
	void setPort(const quint16& value);
	void setPort(const QString& value);

	float getLongitude() const;
	void setLongitude(float value);
	void setLongitude(const QString& value);

	float getLatitude() const;
	void setLatitude(float value);
	void setLatitude(const QString& value);

    float getHeight() const;
    void setHeight(float value);
    void setHeight(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

    ReceiverInBuffer toReceiverInBuffer();

private:
    QString receiverName;
    QString ipAddress;
    quint16 port;
	float longitude;
	float latitude;
    float height;
    QString detail;
};

#endif // RECEIVER_H
