#ifndef IGMASSTATION_H
#define IGMASSTATION_H

#include "smam_component_header.h"

class iGMASStation
{
public:
    iGMASStation();

    QString getStationName() const;
    void setStationName(const QString& value);

    QString getMountPoint() const;
    void setMountPoint(const QString& value);

    int getMemID() const;
    void setMemID(int value);
    void setMemID(const QString& value);

    double getLongitude() const;
    void setLongitude(double value);
    void setLongitude(const QString& value);

    double getLatitude() const;
    void setLatitude(double value);
    void setLatitude(const QString& value);

    double getHeight() const;
    void setHeight(double value);
    void setHeight(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

    iGMASStationInBuffer toIGMASStationInBuffer();

private:
    QString stationName;
    QString mountPoint;
    int memID;
    double longitude;
    double latitude;
    double height;
    QString detail;
};

#endif // IGMASSTATION_H
