#include <QDateTime>
#include <QStringList>

#include "general_functions.h"

#include "main_component_header.h"

const QRegExp GeneralFunctions::nameRX("^[a-zA-Z0-9].+$");
const QRegExp GeneralFunctions::ipAddressRX("^(?:(?:25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)\\.){3}(?:25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)$");
const QRegExp GeneralFunctions::longitudeRX("^[+-]?(?:1[0-7]\\d|[1-9]?\\d)(?:\\.\\d{2,})$");
const QRegExp GeneralFunctions::latitudeRX("^[+-]?(?:[1-8]?\\d)(?:\\.\\d{2,})$");
const QRegExp GeneralFunctions::heightRX("^[+-]?(?:(?:[1-9]\\d*|0)\\.\\d{2,})$");
const QRegExp GeneralFunctions::mountPointRX("^(?:[a-zA-Z0-9]{4,10})$");
const QRegExp GeneralFunctions::memIDRX("^(?:\\d+)$");
const QRegExp GeneralFunctions::usernameRX("^[a-zA-Z0-9].+$");
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

bool GeneralFunctions::checkPortString(const QString& s)
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

bool GeneralFunctions::checkMountPointString(const QString& s)
{
    if (s == 0) {
        return false;
    }
    return mountPointRX.exactMatch(s);
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
    return usernameRX.exactMatch(s);
}

bool GeneralFunctions::checkPasswordString(const QString &s)
{
    if (s == 0) {
        return false;
    }
    return passwordRX.exactMatch(s);
}

QString GeneralFunctions::convertDMSToQString(const DMS& value)
{
    QString result = "";
    result += QString::number(value.degree) + "°";
    result += QString::number(value.minute) + "′";
    result += QString::number(value.second) + ".";
    result += QString::number(value.fractionalPart) + "″";
    return result;
}

DMS GeneralFunctions::convertQStringToDMS(const QString& value)
{
    DMS result;
    QStringList splitResult = value.split(QRegExp("[°.′″]"), QString::SkipEmptyParts);
    result.degree = splitResult[0].toInt();
    result.minute = splitResult[1].toInt();
    result.second = splitResult[2].toInt();
    result.fractionalPart = splitResult[3].toInt();
    return result;
}

void GeneralFunctions::writeMessageToFront(const QString& message)
{
    SoftWorkStatus status;
    status.messageType = 1;
    status.messageTime = QDateTime::currentDateTime().toTime_t();
    qstrcpy(status.messageContent, message.toStdString().c_str());
    SoftWorkStatusWriteFunc(6, status);
}
