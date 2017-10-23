#ifndef CONFIGHELPER_H
#define CONFIGHELPER_H

#include <QDomDocument>
#include <QList>
#include <QBitArray>

#include "bean/standard_station.h"
#include "bean/igmas_station.h"
#include "bean/igmas_datacenter.h"
#include "bean/other_center.h"

class ConfigHelper
{
public:
    static bool init();
    static void update();
    static QList<int> componentStateCheckIntervals;
    static QList<StandardStation*> standardStations;
    static QList<iGMASStation*> iGMASStations;
    static QList<iGMASDataCenter*> iGMASDataCenters;
    static QList<OtherCenter*> otherCenters;

    static iGMASDataCenter* getIGMASDataCenterByCenterID(int centerID);
    static int findFreeReceiverMemID();
    static int findFreeIGMASStationMemID();
    static void clearReceiverMemID(int memID);
    static void clearIGMASStationMemID(int memID);
    static int getNewIGMASDataCenterID();
    static int getNewOtherCenterID();
    static void deleteIGMASDataCenter(int centerID);

private:
    ConfigHelper();
    ConfigHelper(const ConfigHelper&);
    ConfigHelper& operator=(const ConfigHelper&);

    static void getComponentStateCheckIntervalsFromDOM();
    static void setComponentStateCheckIntervalsToDOM();
    static void getStandardStationsFromDOM();
    static void setStandardStationsToDOM();
    static void getIGMASStationsFromDOM();
    static void setIGMASStationsToDOM();
    static void getIGMASDataCentersFromDOM();
    static void setIGMASDataCentersToDOM();
    static void getOtherCentersFromDOM();
    static void setOtherCentersToDOM();
    static void writeConfigFile();

    static QString configFileName;
    static QDomDocument root;

    static QBitArray receiverMemIDArray;
    static QBitArray iGMASStationMemIDArray;
    static qint32 maxIGMASDataCenterID;
    static qint32 maxOtherCenterID;
};

#endif // CONFIGHELPER_H
