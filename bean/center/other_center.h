#ifndef OTHERCENTER_H
#define OTHERCENTER_H

#include "base_center.h"
#include "smam_component_header.h"

class OtherCenter : public BaseCenter
{
public:
    OtherCenter();
    OtherCenterInBuffer toOtherCenterInBuffer();

    QString getUserName() const;
    void setUserName(const QString& value);

    QString getPassword() const;
    void setPassword(const QString& value);

private:
    QString userName;
    QString password;
};

#endif // OTHERCENTER_H
