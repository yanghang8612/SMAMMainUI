#include "other_center.h"

OtherCenter::OtherCenter()
{

}

OtherCenterInBuffer OtherCenter::toOtherCenterInBuffer()
{
    OtherCenterInBuffer otherCenterInBuffer;
    qMemCopy(otherCenterInBuffer.centerName, centerName.toStdString().c_str(), centerName.length());
    qMemCopy(otherCenterInBuffer.ipAddress, ipAddress.toStdString().c_str(), ipAddress.length());
    otherCenterInBuffer.port = port;
    return otherCenterInBuffer;
}

