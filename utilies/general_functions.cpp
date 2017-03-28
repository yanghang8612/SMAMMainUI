#include <QDateTime>

#include "general_functions.h"
#include "main_component_header.h"

const QRegExp GeneralFunctions::nameRX("^[a-zA-Z0-9].+$");
const QRegExp GeneralFunctions::ipAddressRX("^(?:(?:25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)\\.){3}(?:25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)$");
const QRegExp GeneralFunctions::longitudeRX("^[+-]?(?:1[0-7]\\d|[1-9]?\\d)(?:\\.\\d{2,})$");
const QRegExp GeneralFunctions::latitudeRX("^[+-]?(?:[1-8]?\\d)(?:\\.\\d{2,})$");
const QRegExp GeneralFunctions::heightRX("^[+-]?(?:(?:[1-9]\\d*|0)\\.\\d{2,})$");
const QRegExp GeneralFunctions::mountRX("^(?:[0-9A-Z]{4})$");
const QRegExp GeneralFunctions::memIDRX("^(?:\\d+)$");
const QRegExp GeneralFunctions::userNameRX("^[a-zA-Z0-9].+$");
const QRegExp GeneralFunctions::passwordRX("^.{4,}$");

GeneralFunctions::GeneralFunctions()
{
}

bool GeneralFunctions::checkNameString(const QString& s)
{
    if (s == 0) {
        return false;
    }
    return nameRX.exactMatch(s);
}

bool GeneralFunctions::checkIPAddressString(const QString& s)
{
    if (s == 0) {
        return false;
    }
    return ipAddressRX.exactMatch(s);
}

bool GeneralFunctions::checkIPPortString(const QString& s)
{
    if (s == 0) {
        return false;
    }
    bool ok;
    int port = s.toInt(&ok);
    if (!ok || port > 65535 || port < 0)
        return false;
    else
        return true;
}

bool GeneralFunctions::checkLongitudeString(const QString &s)
{
    if (s == 0) {
        return false;
    }
    return longitudeRX.exactMatch(s);
}

bool GeneralFunctions::checkLatitudeString(const QString &s)
{
    if (s == 0) {
        return false;
    }
    return latitudeRX.exactMatch(s);
}

bool GeneralFunctions::checkHeightString(const QString& s)
{
    if (s == 0) {
        return false;
    }
    return heightRX.exactMatch(s);
}

bool GeneralFunctions::checkMountString(const QString& s)
{
    if (s == 0) {
        return false;
    }
    return mountRX.exactMatch(s);
}

bool GeneralFunctions::checkMemIDString(const QString& s)
{
    if (s == 0) {
        return false;
    }
    return memIDRX.exactMatch(s);
}

bool GeneralFunctions::checkUserNameString(const QString &s)
{
    if (s == 0) {
        return false;
    }
    return userNameRX.exactMatch(s);
}

bool GeneralFunctions::checkPasswordString(const QString &s)
{
    if (s == 0) {
        return false;
    }
    return passwordRX.exactMatch(s);
}

void GeneralFunctions::writeMessageToFront(const QString& message)
{
    SoftWorkStatus status;
    status.messageType = 1;
    status.messageTime = QDateTime::currentDateTime().toTime_t();
    qMemSet(status.messageContent, 0, sizeof(status.messageContent));
    qMemCopy(status.messageContent, message.toStdString().c_str(), message.length());

    if (SoftWorkStatusWriteFunc != 0) {
        SoftWorkStatusWriteFunc(6, status);
    }
}
