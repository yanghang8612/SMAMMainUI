#ifndef BASECENTER_H
#define BASECENTER_H

#include "common.h"

class BaseCenter
{
public:
    BaseCenter();

    QString getCenterName() const;
    void setCenterName(const QString& value);

    QString getIpAddress() const;
    void setIpAddress(const QString& value);

    quint16 getPort() const;
    void setPort(const quint16& value);
    void setPort(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

protected:
    QString centerName;
    QString ipAddress;
    quint16 port;
    QString detail;

private:
    Q_DISABLE_COPY(BaseCenter)
};

#endif // BASECENTER_H
