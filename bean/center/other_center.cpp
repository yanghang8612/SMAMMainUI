#include "other_center.h"

OtherCenter::OtherCenter()
{}

QString OtherCenter::getUserName() const
{
    return userName;
}

void OtherCenter::setUserName(const QString& value)
{
    userName = value;
}

QString OtherCenter::getPassword() const
{
    return password;
}

void OtherCenter::setPassword(const QString& value)
{
    password = value;
}

OtherCenterInBuffer OtherCenter::toOtherCenterInBuffer()
{
    OtherCenterInBuffer otherCenterInBuffer;
    qMemSet(&otherCenterInBuffer, 0, sizeof(OtherCenterInBuffer));
    qMemCopy(otherCenterInBuffer.centerName, centerName.toStdString().c_str(), centerName.length());
    qMemCopy(otherCenterInBuffer.userName, userName.toStdString().c_str(), userName.length());
    qMemCopy(otherCenterInBuffer.password, password.toStdString().c_str(), password.length());
    qMemCopy(otherCenterInBuffer.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    otherCenterInBuffer.port = port;
    qMemCopy(otherCenterInBuffer.detail, detail.toStdString().c_str(), detail.length());
    return otherCenterInBuffer;
}



