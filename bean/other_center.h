#ifndef OTHERCENTER_H
#define OTHERCENTER_H

#include "smam_component_header.h"

class OtherCenter
{
public:
    OtherCenter();

    QString getCenterName() const;
    void setCenterName(const QString& value);

    QString getIpAddress() const;
    void setIpAddress(const QString& value);

    quint16 getPort() const;
    void setPort(const quint16& value);
    void setPort(const QString& value);

    QString getUsername() const;
    void setUsername(const QString& value);

    QString getPassword() const;
    void setPassword(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

    OtherCenterInBuffer toOtherCenterInBuffer();

private:
    QString centerName;
    QString ipAddress;
    quint16 port;
    QString username;
    QString password;
    QString detail;
};

#endif // OTHERCENTER_H
