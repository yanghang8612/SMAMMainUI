#ifndef MONITORSTATION_H
#define MONITORSTATION_H

#include <QString>

#include "smam_component_header.h"

class MonitorStation
{
public:
    enum StationState {UNCONNECTED, CONNECTED, NORMAl, NODATA};

public:
    MonitorStation();
    ~MonitorStation();

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

    DMS getLongitude() const;
    void setLongitude(const DMS& value);
    void setLongitude(const QString& value);

    DMS getLatitude() const;
    void setLatitude(const DMS& value);
    void setLatitude(const QString& value);

    double getHeight() const;
    void setHeight(double value);
    void setHeight(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

    QString getDataCenters() const;
    void setDataCenters(const QString& value);
    void deleteDataCenter(int centerID);

    StationState getState() const;
    void setState(const StationState& value);

    MonitorStationInBuffer* getBufferItem();
    MonitorStationInBuffer toMonitorStationInBuffer();

private:
    MonitorStationInBuffer* bufferItem;
    int memID;
    bool isAvailable;
    QString stationName;
    QString mountPoint;
    DMS longitude;
    DMS latitude;
    double height;
    QString detail;
    QString dataCenters;
    StationState state;
};

#endif // MONITORSTATION_H
