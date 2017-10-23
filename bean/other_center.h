#ifndef OTHERCENTER_H
#define OTHERCENTER_H

#include <QString>

#include "smam_component_header.h"

class OtherCenter
{
public:
    OtherCenter();
    ~OtherCenter();

    qint32 getCenterID() const;
    void setCenterID(const qint32& value);
    void setCenterID(const QString& value);

    QString getCenterName() const;
    void setCenterName(const QString& value);

    QString getIpAddress() const;
    void setIpAddress(const QString& value);

    QString getUsername() const;
    void setUsername(const QString& value);

    QString getPassword() const;
    void setPassword(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

    OtherCenterInBuffer* getBufferItem();
    OtherCenterInBuffer toOtherCenterInBuffer();

private:
    OtherCenterInBuffer* bufferItem;
    qint32 centerID;
    QString centerName;
    QString ipAddress;
    QString username;
    QString password;
    QString centerDetail;
};

#endif // OTHERCENTER_H
