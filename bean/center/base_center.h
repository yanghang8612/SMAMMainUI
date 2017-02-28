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

    QString getDetail() const;
    void setDetail(const QString& value);

protected:
    QString centerName;
    QString ipAddress;
    QString detail;

private:
    Q_DISABLE_COPY(BaseCenter)
};

#endif // BASECENTER_H
