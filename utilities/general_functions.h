#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H

#include <QRegExp>

#include "common.h"
#include "smam_component_header.h"

class GeneralFunctions
{
private:
    GeneralFunctions();

public:
    static const QRegExp nameRX;
    static const QRegExp ipAddressRX;
    static const QRegExp longitudeRX;
    static const QRegExp latitudeRX;
    static const QRegExp heightRX;
    static const QRegExp mountPointRX;
    static const QRegExp memIDRX;
    static const QRegExp usernameRX;
    static const QRegExp passwordRX;

    static bool checkNameString(const QString& s);
    static bool checkIPAddressString(const QString& s);
    static bool checkPortString(const QString& s);
    static bool checkLongitudeString(const QString& s);
    static bool checkLatitudeString(const QString& s);
    static bool checkHeightString(const QString& s);
    static bool checkMountPointString(const QString& s);
    static bool checkMemIDString(const QString& s);
    static bool checkUserNameString(const QString& s);
    static bool checkPasswordString(const QString& s);

    static QString convertDMSToQString(const DMS& value);
    static DMS convertQStringToDMS(const QString& value);
    static void writeMessageToFront(const QString& message);
};

#endif // GENERALFUNCTIONS_H
