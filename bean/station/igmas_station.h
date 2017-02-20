#ifndef IGMASSTATION_H
#define IGMASSTATION_H

#include "base_station.h"
#include "smam_component_header.h"

class IGMASStation : public BaseStation
{
public:
	IGMASStation();

    bool getIsAvailable() const;
    void setIsAvailable(bool value);
    void setIsAvailable(const QString& value);
    void setIsAvailable(int value);

    QString getMount() const;
    void setMount(const QString& value);

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

    IGMASStationInBuffer toiGMASStationInBuffer();

private:
    bool isAvailable;
    QString mount;
    int memID;
    double longitude;
    double latitude;
    double height;
};

#endif // IGMASSTATION_H
