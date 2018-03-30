#ifndef CONFIGHELPER_H
#define CONFIGHELPER_H

#include <QDomDocument>
#include <QList>
#include <QBitArray>

#include "bean/standard_station.h"
#include "bean/monitor_station.h"
#include "bean/data_center.h"
#include "bean/other_center.h"

class ConfigHelper
{
public:
    static bool init();
    static void update();
    static QList<int> componentStateCheckIntervals;
    static QList<StandardStation*> standardStations;
    static QList<MonitorStation*> monitorStations;
    static QList<DataCenter*> dataCenters;
    static QList<OtherCenter*> otherCenters;

    static DataCenter* getDataCenterByCenterID(int centerID);
    static int findFreeReceiverMemID();
    static int findFreeMonitorStationMemID();
    static void clearReceiverMemID(int memID);
    static void clearMonitorStationMemID(int memID);
    static int getNewDataCenterID();
    static int getNewOtherCenterID();
    static void deleteDataCenter(int centerID);

private:
    ConfigHelper();
    ConfigHelper(const ConfigHelper&);
    ConfigHelper& operator=(const ConfigHelper&);

    static void getComponentStateCheckIntervalsFromDOM();
    static void setComponentStateCheckIntervalsToDOM();
    static void getStandardStationsFromDOM();
    static void setStandardStationsToDOM();
    static void getMonitorStationsFromDOM();
    static void setMonitorStationsToDOM();
    static void getDataCentersFromDOM();
    static void setDataCentersToDOM();
    static void getOtherCentersFromDOM();
    static void setOtherCentersToDOM();
    static void writeConfigFile();

    static QString configFileName;
    static QDomDocument root;

    static QBitArray receiverMemIDArray;
    static QBitArray monitorStationMemIDArray;
    static qint32 maxDataCenterID;
    static qint32 maxOtherCenterID;
};

#endif // CONFIGHELPER_H
