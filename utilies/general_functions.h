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

    static const QRegExp nameRX;
    static const QRegExp ipAddressRX;
    static const QRegExp longitudeRX;
    static const QRegExp latitudeRX;
};

#endif // GENERALFUNCTIONS_H
