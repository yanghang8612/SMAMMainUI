#ifndef IGMASSTATION_H
#define IGMASSTATION_H

#include <QString>

#include "smam_component_header.h"

class iGMASStation
{
public:
    iGMASStation();
    ~iGMASStation();

    QString getDescription();

    int getMemID() const;
    void setMemID(int value);
    void setMemID(const QString& value);

    bool getIsAvailable() const;
    void setIsAvailable(bool value);
    void setIsAvailable(const QString& value);

    QString getStationName() const;
    void setStationName(const QString& value);

    QString getMountPoint() const;
    void setMountPoint(const QString& value);

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

    QString getDataCenters() const;
    void setDataCenters(const QString& value);
    void deleteDataCenter(int centerID);

    iGMASStationInBuffer* getBufferItem();
    iGMASStationInBuffer toIGMASStationInBuffer();

private:
    iGMASStationInBuffer* bufferItem;
    int memID;
    bool isAvailable;
    QString stationName;
    QString mountPoint;
    double longitude;
    double latitude;
    double height;
    QString detail;
    QString dataCenters;
};

#endif // IGMASSTATION_H
