﻿#include <QFile>
#include <QDebug>
#include <QStringList>

#include "config_helper.h"
#include "common.h"
#include "utilities/general_functions.h"

extern DeploymentType::Value deploymentType;

extern void* receiverSharedBufferPointer;
extern void* monitorStationSharedBufferPointer;
extern void* dataCenterSharedBufferPointer;
extern void* otherCenterSharedBufferPointer;

QList<int> ConfigHelper::componentStateCheckIntervals;
QList<StandardStation*> ConfigHelper::standardStations;
QList<MonitorStation*> ConfigHelper::monitorStations;
QList<DataCenter*> ConfigHelper::dataCenters;
QList<OtherCenter*> ConfigHelper::otherCenters;
QString ConfigHelper::configFileName;
QDomDocument ConfigHelper::root;
QBitArray ConfigHelper::receiverMemIDArray;
QBitArray ConfigHelper::monitorStationMemIDArray;
qint32 ConfigHelper::maxDataCenterID = 0;
qint32 ConfigHelper::maxOtherCenterID = 0;

bool ConfigHelper::init()
{
    receiverMemIDArray.resize(RECEIVER_MAXITEMCOUNT);
    monitorStationMemIDArray.resize(MONITORSTATION_MAXITEMCOUNT);
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            ConfigHelper::configFileName = XJ_CONFIGFILE_PATH;
            break;
        case DeploymentType::BJ_CENTER:
            ConfigHelper::configFileName = BJ_CONFIGFILE_PATH;
            break;
    }

    QFile configFile(configFileName);
    if (!configFile.open(QIODevice::ReadOnly | QFile::Text)) {
        qDebug() << "SMAMMainUI:" << "Configfile" << configFileName << "is not existed, create it";
        if (!configFile.open(QIODevice::ReadWrite | QFile::Text)) {
            qDebug() << "SMAMMainUI:" << "Create configfile" << configFileName << "error";
            return false;
        }
        else {
            root.appendChild(root.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\""));
            QDomElement rootElement = root.createElement("BDLSS");
            root.appendChild(rootElement);
            QDomElement settingElement = root.createElement("SETTINGS");
            rootElement.appendChild(settingElement);
            QDomElement intervalElement = root.createElement("INTERVALS");
            settingElement.appendChild(intervalElement);
            for (int i = 0; i < COMPONENT_COUNT; i++) {
                intervalElement.appendChild(root.createElement(COMPONENT_NAME[i]));
                intervalElement.lastChild().appendChild(root.createTextNode("3"));
            }

            rootElement.appendChild(root.createElement("STATIONS"));
            if (deploymentType == DeploymentType::BJ_CENTER) {
                rootElement.appendChild(root.createElement("DATACENTERS"));
            }
            rootElement.appendChild(root.createElement("OTHERCENTERS"));

            QTextStream out(&configFile);
            out.setCodec("UTF-8");
            root.save(out, 4, QDomNode::EncodingFromTextStream);
            configFile.close();
        }
    }
    else {
        QString errorStr;
        int errorLine, errorColumn;
        if (!root.setContent(&configFile, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug() << "SMAMMainUI:" << "QDomDocument set content error, the error message is" << errorStr;
            return false;
        }
        configFile.close();

        getComponentStateCheckIntervalsFromDOM();
        switch (deploymentType) {
            case DeploymentType::XJ_CENTER:
                getStandardStationsFromDOM();
                break;
            case DeploymentType::BJ_CENTER:
                getMonitorStationsFromDOM();
                getDataCentersFromDOM();
                getOtherCentersFromDOM();
                break;
        }
        maxDataCenterID = dataCenters.size() == 0 ? 0 : dataCenters.last()->getCenterID();
        maxOtherCenterID = otherCenters.size() == 0 ? 0 : otherCenters.last()->getCenterID();
    }
    return true;
}

void ConfigHelper::update()
{
    root.clear();
    root.appendChild(root.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\""));
    root.appendChild(root.createElement("BDLSS"));

    setComponentStateCheckIntervalsToDOM();
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            setStandardStationsToDOM();
            break;
        case DeploymentType::BJ_CENTER:
            setMonitorStationsToDOM();
            setDataCentersToDOM();
            setOtherCentersToDOM();
            break;
    }
    writeConfigFile();
}

DataCenter* ConfigHelper::getDataCenterByCenterID(int centerID)
{
    for (int i = 0; i < dataCenters.size(); i++) {
        if (centerID == dataCenters[i]->getCenterID()) {
            return dataCenters[i];
        }
    }
    return 0;
}

int ConfigHelper::findFreeReceiverMemID()
{
    for (int i = 0; i < RECEIVER_MAXITEMCOUNT; i++) {
        if (!receiverMemIDArray[i]) {
            receiverMemIDArray.setBit(i);
            return i + RECEIVER_MEMID_START_INDEX;
        }
    }
    qDebug() << "SMAMMainUI:" << "Do not find no free receiver memid";
    return -1;
}

int ConfigHelper::findFreeMonitorStationMemID()
{
    for (int i = 0; i < MONITORSTATION_MAXITEMCOUNT; i++) {
        if (!monitorStationMemIDArray[i]) {
            monitorStationMemIDArray.setBit(i);
            return i + MONITORSTATION_MEMID_START_INDEX;
        }
    }
    qDebug() << "SMAMMainUI:" << "Do not find free monitor station memid";
    return -1;
}

void ConfigHelper::clearReceiverMemID(int memID)
{
    receiverMemIDArray.clearBit(memID - RECEIVER_MEMID_START_INDEX);
}

void ConfigHelper::clearMonitorStationMemID(int memID)
{
    monitorStationMemIDArray.clearBit(memID - MONITORSTATION_MEMID_START_INDEX);
}

int ConfigHelper::getNewDataCenterID()
{
    return ++maxDataCenterID;
}

int ConfigHelper::getNewOtherCenterID()
{
    return ++maxOtherCenterID;
}

void ConfigHelper::deleteDataCenter(int centerID)
{
    foreach (MonitorStation* station, monitorStations) {
        QStringList dataCenterList = station->getDataCenters().split(",", QString::SkipEmptyParts);
        if (dataCenterList.contains(QString::number(centerID))) {
            dataCenterList.removeOne(QString::number(centerID));
            QString newDataCenters = "";
            for (int i = 0; i < dataCenterList.count(); i++) {
                newDataCenters += (dataCenterList[i] + ",");
            }
            station->setDataCenters(newDataCenters);
        }
    }
}

void ConfigHelper::getComponentStateCheckIntervalsFromDOM()
{
    QDomNode intervalRoot = root.namedItem("BDLSS").namedItem("SETTINGS").namedItem("INTERVALS");
    for (QDomNode intervalNode = intervalRoot.firstChild(); !intervalNode.isNull(); intervalNode = intervalNode.nextSibling()) {
        componentStateCheckIntervals.append(intervalNode.toElement().text().toInt());
    }
}

void ConfigHelper::setComponentStateCheckIntervalsToDOM()
{
    QDomElement settingRoot = root.createElement("SETTINGS");
    QDomElement intervalRoot = root.createElement("INTERVALS");
    for (int i = 0; i < COMPONENT_COUNT; i++) {
        intervalRoot.appendChild(root.createElement(COMPONENT_NAME[i]));
        intervalRoot.lastChild().appendChild(root.createTextNode(QString::number(componentStateCheckIntervals[i])));
    }
    settingRoot.appendChild(intervalRoot);
    root.namedItem("BDLSS").appendChild(settingRoot);
}

void ConfigHelper::getStandardStationsFromDOM()
{
    QDomNode stationRoot = root.namedItem("BDLSS").namedItem("STATIONS");
    for (QDomNode stationNode = stationRoot.firstChild(); !stationNode.isNull(); stationNode = stationNode.nextSibling()) {
        StandardStation* station = new StandardStation();
        station->setStationName(stationNode.namedItem("STATIONNAME").toElement().text());
        station->setType(stationNode.namedItem("DEPLOYMENTTYPE").toElement().text());
        station->setDetail(stationNode.namedItem("DETAIL").toElement().text());
        for (QDomNode receiverNode = stationNode.namedItem("RECEIVERS").firstChild(); !receiverNode.isNull(); receiverNode = receiverNode.nextSibling()) {
            Receiver* receiver = new Receiver();
            receiver->setMemID(receiverNode.namedItem("MEMID").toElement().text());
            receiver->setReceiverName(receiverNode.namedItem("RECEIVERNAME").toElement().text());
            receiver->setPassword(receiverNode.namedItem("PASSWORD").toElement().text());
            receiver->setIpAddress(receiverNode.namedItem("IPADDRESS").toElement().text());
            receiver->setPort(receiverNode.namedItem("IPPORT").toElement().text());
            receiver->setMountPoint(receiverNode.namedItem("MOUNTPOINT").toElement().text());
            receiver->setLongitude(receiverNode.namedItem("LONGITUDE").toElement().text());
            receiver->setLatitude(receiverNode.namedItem("LATITUDE").toElement().text());
            receiver->setHeight(receiverNode.namedItem("HEIGHT").toElement().text());
            receiver->setDetail(receiverNode.namedItem("DETAIL").toElement().text());
            station->addReceiver(receiver);
            ConfigHelper::receiverMemIDArray.setBit(receiver->getMemID() - RECEIVER_MEMID_START_INDEX);
        }
        standardStations << station;
    }
}

void ConfigHelper::setStandardStationsToDOM()
{
    QDomElement stationRoot = root.createElement("STATIONS");
    for (int i = 0; i < standardStations.size(); i++) {
        StandardStation* station = standardStations[i];
        QDomElement stationNode = root.createElement("STATION");

        stationNode.appendChild(root.createElement("STATIONNAME"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getStationName()));

        stationNode.appendChild(root.createElement("DEPLOYMENTTYPE"));
        stationNode.lastChild().appendChild(root.createTextNode(QString::number((int) deploymentType)));

        stationNode.appendChild(root.createElement("DETAIL"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getDetail()));

        QDomElement receiverRoot = root.createElement("RECEIVERS");
        stationNode.appendChild(receiverRoot);
        for (int j = 0; j < station->getReceivers().size(); j++) {
            Receiver* receiver = station->getReceivers()[j];
            QDomElement receiverNode = root.createElement("RECEIVER");

            receiverNode.appendChild(root.createElement("MEMID"));
            receiverNode.lastChild().appendChild(root.createTextNode(QString::number(receiver->getMemID())));

            receiverNode.appendChild(root.createElement("RECEIVERNAME"));
            receiverNode.lastChild().appendChild(root.createTextNode(receiver->getReceiverName()));

            receiverNode.appendChild(root.createElement("PASSWORD"));
            receiverNode.lastChild().appendChild(root.createTextNode(receiver->getPassword()));

            receiverNode.appendChild(root.createElement("IPADDRESS"));
            receiverNode.lastChild().appendChild(root.createTextNode(receiver->getIpAddress()));

            receiverNode.appendChild(root.createElement("IPPORT"));
            receiverNode.lastChild().appendChild(root.createTextNode(QString::number(receiver->getPort())));

            receiverNode.appendChild(root.createElement("MOUNTPOINT"));
            receiverNode.lastChild().appendChild(root.createTextNode(receiver->getMountPoint()));

            receiverNode.appendChild(root.createElement("LONGITUDE"));
            receiverNode.lastChild().appendChild(root.createTextNode(GeneralFunctions::convertDMSToQString(receiver->getLongitude())));

            receiverNode.appendChild(root.createElement("LATITUDE"));
            receiverNode.lastChild().appendChild(root.createTextNode(GeneralFunctions::convertDMSToQString(receiver->getLatitude())));

            receiverNode.appendChild(root.createElement("HEIGHT"));
            receiverNode.lastChild().appendChild(root.createTextNode(QString::number(receiver->getHeight())));

            receiverNode.appendChild(root.createElement("DETAIL"));
            receiverNode.lastChild().appendChild(root.createTextNode(receiver->getDetail()));

            receiverRoot.appendChild(receiverNode);
        }
        stationRoot.appendChild(stationNode);
    }
    root.namedItem("BDLSS").appendChild(stationRoot);
}

void ConfigHelper::getMonitorStationsFromDOM()
{
    QDomNode stationRoot = root.namedItem("BDLSS").namedItem("STATIONS");
    for (QDomNode stationNode = stationRoot.firstChild(); !stationNode.isNull(); stationNode = stationNode.nextSibling()) {
        MonitorStation* station = new MonitorStation();
        station->setMemID(stationNode.namedItem("MEMID").toElement().text());
        station->setIsAvailable(stationNode.namedItem("ISAVAILABLE").toElement().text());
        station->setStationName(stationNode.namedItem("STATIONNAME").toElement().text());
        station->setMountPoint(stationNode.namedItem("MOUNTPOINT").toElement().text());
        station->setLongitude(stationNode.namedItem("LONGITUDE").toElement().text());
        station->setLatitude(stationNode.namedItem("LATITUDE").toElement().text());
        station->setHeight(stationNode.namedItem("HEIGHT").toElement().text());
        station->setDetail(stationNode.namedItem("DETAIL").toElement().text());
        station->setDataCenters(stationNode.namedItem("DATACENTERS").toElement().text());
        monitorStationMemIDArray.setBit(station->getMemID() - MONITORSTATION_MEMID_START_INDEX);
        monitorStations << station;
    }
}

void ConfigHelper::setMonitorStationsToDOM()
{
    QDomElement stationRoot = root.createElement("STATIONS");
    for (int i = 0; i < monitorStations.size(); i++) {
        MonitorStation* station = monitorStations[i];
        QDomElement stationNode = root.createElement("STATION");

        stationNode.appendChild(root.createElement("MEMID"));
        stationNode.lastChild().appendChild(root.createTextNode(QString::number(station->getMemID())));

        stationNode.appendChild(root.createElement("ISAVAILABLE"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getIsAvailable() ? "true" : "false"));

        stationNode.appendChild(root.createElement("STATIONNAME"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getStationName()));

        stationNode.appendChild(root.createElement("MOUNTPOINT"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getMountPoint()));

        stationNode.appendChild(root.createElement("LONGITUDE"));
        stationNode.lastChild().appendChild(root.createTextNode(GeneralFunctions::convertDMSToQString(station->getLongitude())));

        stationNode.appendChild(root.createElement("LATITUDE"));
        stationNode.lastChild().appendChild(root.createTextNode(GeneralFunctions::convertDMSToQString(station->getLatitude())));

        stationNode.appendChild(root.createElement("HEIGHT"));
        stationNode.lastChild().appendChild(root.createTextNode(QString::number(station->getHeight())));

        stationNode.appendChild(root.createElement("DETAIL"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getDetail()));

        stationNode.appendChild(root.createElement("DATACENTERS"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getDataCenters()));

        stationRoot.appendChild(stationNode);
    }
    root.namedItem("BDLSS").appendChild(stationRoot);
}

void ConfigHelper::getDataCentersFromDOM()
{
    QDomNode centerRoot = root.namedItem("BDLSS").namedItem("DATACENTERS");
    for (QDomNode centerNode = centerRoot.firstChild(); !centerNode.isNull(); centerNode = centerNode.nextSibling()) {
        DataCenter* center = new DataCenter();
        center->setCenterID(centerNode.namedItem("CENTERID").toElement().text());
        center->setCenterName(centerNode.namedItem("CENTERNAME").toElement().text());
        center->setMasterIPAddress(centerNode.namedItem("MASTERIP").toElement().text());
        center->setMasterPort(centerNode.namedItem("MASTERPORT").toElement().text());
        center->setSlaveIPAddress(centerNode.namedItem("SLAVEIP").toElement().text());
        center->setSlavePort(centerNode.namedItem("SLAVEPORT").toElement().text());
        center->setUsername(centerNode.namedItem("USERNAME").toElement().text());
        center->setPassword(centerNode.namedItem("PASSWORD").toElement().text());
        center->setCenterDetail(centerNode.namedItem("DETAIL").toElement().text());
        dataCenters << center;
    }
}

void ConfigHelper::setDataCentersToDOM()
{
    QDomElement centerRoot = root.createElement("DATACENTERS");
    for (int i = 0; i < dataCenters.size(); i++) {
        DataCenter* center = dataCenters[i];
        QDomElement centerNode = root.createElement("CENTER");

        centerNode.appendChild(root.createElement("CENTERID"));
        centerNode.lastChild().appendChild(root.createTextNode(QString::number(center->getCenterID())));

        centerNode.appendChild(root.createElement("CENTERNAME"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getCenterName()));

        centerNode.appendChild(root.createElement("MASTERIP"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getMasterIPAddress()));

        centerNode.appendChild(root.createElement("MASTERPORT"));
        centerNode.lastChild().appendChild(root.createTextNode(QString::number(center->getMasterPort())));

        centerNode.appendChild(root.createElement("SLAVEIP"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getSlaveIPAddress()));

        centerNode.appendChild(root.createElement("SLAVEPORT"));
        centerNode.lastChild().appendChild(root.createTextNode(QString::number(center->getSlavePort())));

        centerNode.appendChild(root.createElement("USERNAME"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getUsername()));

        centerNode.appendChild(root.createElement("PASSWORD"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getPassword()));

        centerNode.appendChild(root.createElement("DETAIL"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getCenterDetail()));

        centerRoot.appendChild(centerNode);
    }
    root.namedItem("BDLSS").appendChild(centerRoot);
}

void ConfigHelper::getOtherCentersFromDOM()
{
    QDomNode centerRoot = root.namedItem("BDLSS").namedItem("OTHERCENTERS");
    for (QDomNode centerNode = centerRoot.firstChild(); !centerNode.isNull(); centerNode = centerNode.nextSibling()) {
        OtherCenter* center = new OtherCenter();
        center->setCenterID(centerNode.namedItem("CENTERID").toElement().text());
        center->setCenterName(centerNode.namedItem("CENTERNAME").toElement().text());
        center->setIpAddress(centerNode.namedItem("IPADDRESS").toElement().text());
        center->setUsername(centerNode.namedItem("USERNAME").toElement().text());
        center->setPassword(centerNode.namedItem("PASSWORD").toElement().text());
        center->setDetail(centerNode.namedItem("DETAIL").toElement().text());
        otherCenters << center;
    }
}

void ConfigHelper::setOtherCentersToDOM()
{
    QDomElement centerRoot = root.createElement("OTHERCENTERS");
    for (int i = 0; i < otherCenters.size(); i++) {
        OtherCenter* center = otherCenters[i];
        QDomElement centerNode = root.createElement("CENTER");

        centerNode.appendChild(root.createElement("CENTERID"));
        centerNode.lastChild().appendChild(root.createTextNode(QString::number(center->getCenterID())));

        centerNode.appendChild(root.createElement("CENTERNAME"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getCenterName()));

        centerNode.appendChild(root.createElement("IPADDRESS"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getIpAddress()));

        centerNode.appendChild(root.createElement("USERNAME"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getUsername()));

        centerNode.appendChild(root.createElement("PASSWORD"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getPassword()));

        centerNode.appendChild(root.createElement("DETAIL"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getDetail()));

        centerRoot.appendChild(centerNode);
    }
    root.namedItem("BDLSS").appendChild(centerRoot);
}

void ConfigHelper::writeConfigFile()
{
    QFile configFile(configFileName);
    if (!configFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "SMAMMainUI:" << "Configfile" << configFileName << "is not existed, write ConfigFile error";
    }
    else {
        QTextStream out(&configFile);
        root.save(out, 2);
        configFile.close();
    }
}

ConfigHelper::ConfigHelper() {}

ConfigHelper::ConfigHelper(const ConfigHelper&) {}

ConfigHelper& ConfigHelper::operator=(const ConfigHelper&) {}
