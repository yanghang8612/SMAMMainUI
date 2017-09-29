#ifndef IGMASDATACENTER_H
#define IGMASDATACENTER_H

#include "smam_component_header.h"

class iGMASDataCenter
{
public:
    iGMASDataCenter();

    QString getCenterName() const;
    void setCenterName(const QString& value);

    QString getMasterIPAddress() const;
    void setMasterIPAddress(const QString& value);

    quint16 getMasterPort() const;
    void setMasterPort(const quint16& value);
    void setMasterPort(const QString& value);

    QString getSlaveIPAddress() const;
    void setSlaveIPAddress(const QString& value);

    quint16 getSlavePort() const;
    void setSlavePort(const quint16& value);
    void setSlavePort(const QString& value);

    QString getUsername() const;
    void setUsername(const QString& value);

    QString getPassword() const;
    void setPassword(const QString& value);

    QString getCenterDetail() const;
    void setCenterDetail(const QString& value);

    iGMASDataCenterInBuffer toIGMASDataCenterInBuffer();

private:
    QString centerName;
    QString masterIPAddress;
    quint16 masterPort;
    QString slaveIPAddress;
    quint16 slavePort;
    QString username;
    QString password;
    QString centerDetail;
};

#endif // IGMASDATACENTER_H
