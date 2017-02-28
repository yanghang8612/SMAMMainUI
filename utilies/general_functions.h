#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H

#include <QRegExp>

#include "common.h"

class GeneralFunctions
{
private:
    GeneralFunctions();

public:
    static bool checkNameString(const QString& s);
    static bool checkIPAddressString(const QString& s);
    static bool checkIPPortString(const QString& s);
    static bool checkLongitudeString(const QString& s);
    static bool checkLatitudeString(const QString& s);
    static bool checkHeightString(const QString& s);
    static bool checkMountString(const QString& s);
    static bool checkMemIDString(const QString& s);

    static const QRegExp nameRX;
    static const QRegExp ipAddressRX;
    static const QRegExp longitudeRX;
    static const QRegExp latitudeRX;
    static const QRegExp heightRX;
    static const QRegExp mountRX;
    static const QRegExp memIDRX;

    static bool writeMessageToFont(const QString& message);
};

#endif // GENERALFUNCTIONS_H
