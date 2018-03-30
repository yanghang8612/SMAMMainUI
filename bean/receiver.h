#ifndef RECEIVER_H
#define RECEIVER_H

#include <QString>

#include "smam_component_header.h"

class Receiver
{
public:
	Receiver();
    ~Receiver();

    int getMemID() const;
    void setMemID(int value);
    void setMemID(const QString& value);

	QString getReceiverName() const;
	void setReceiverName(const QString& value);

    QString getPassword() const;
    void setPassword(const QString& value);

	QString getIpAddress() const;
	void setIpAddress(const QString& value);

	quint16 getPort() const;
	void setPort(const quint16& value);
    void setPort(const QString& value);

    QString getMountPoint() const;
    void setMountPoint(const QString& value);

    DMS getLongitude() const;
    void setLongitude(const DMS& value);
    void setLongitude(const QString& value);

    DMS getLatitude() const;
    void setLatitude(const DMS& value);
    void setLatitude(const QString& value);

    double getHeight() const;
    void setHeight(double value);
    void setHeight(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

    ReceiverInBuffer* getBufferItem();
    ReceiverInBuffer toReceiverInBuffer();

private:
    ReceiverInBuffer* bufferItem;
    int memID;
    QString receiverName;
    QString password;
    QString ipAddress;
    quint16 port;
    QString mountPoint;
    DMS longitude;
    DMS latitude;
    double height;
    QString receiverDetail;
};

#endif // RECEIVER_H
