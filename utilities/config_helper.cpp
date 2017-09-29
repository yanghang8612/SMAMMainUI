#include <QFile>
#include <QDebug>

#include "config_helper.h"
#include "common.h"

extern DeploymentType::Value deploymentType;

extern void* receiverSharedBufferPointer;
extern void* iGMASStationSharedBufferPointer;
extern void* iGMASDataCenterSharedBufferPointer;
extern void* otherCenterSharedBufferPointer;

QList<int> ConfigHelper::componentStateCheckIntervals;
QList<StandardStation*> ConfigHelper::standardStations;
QList<iGMASStation*> ConfigHelper::iGMASStations;
QList<iGMASDataCenter*> ConfigHelper::iGMASDataCenters;
QList<OtherCenter*> ConfigHelper::otherCenters;
QString ConfigHelper::configFileName;
QDomDocument ConfigHelper::root;
QBitArray ConfigHelper::receiverMemIDArray;
QBitArray ConfigHelper::iGMASStationMemIDArray;
SharedBuffer* ConfigHelper::receiverSharedBuffer;
SharedBuffer* ConfigHelper::iGMASStationSharedBuffer;
SharedBuffer* ConfigHelper::iGMASDataCenterSharedBuffer;
SharedBuffer* ConfigHelper::otherCenterSharedBuffer;

bool ConfigHelper::init()
{
    receiverMemIDArray.resize(RECEIVER_MAXITEMCOUNT);
    iGMASStationMemIDArray.resize(IGMASSTATION_MAXITEMCOUNT);
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            ConfigHelper::configFileName = XJ_CONFIGFILE_PATH;
            receiverSharedBuffer = (receiverSharedBufferPointer == 0) ? 0 : new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                                                                 SharedBuffer::ONLY_WRITE,
                                                                                 receiverSharedBufferPointer,
                                                                                 sizeof(ReceiverInBuffer));
            break;
        case DeploymentType::BJ_CENTER:
            ConfigHelper::configFileName = BJ_CONFIGFILE_PATH;
            iGMASStationSharedBuffer = (iGMASStationSharedBufferPointer == 0) ? 0 : new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                                                                        SharedBuffer::ONLY_WRITE,
                                                                                        iGMASStationSharedBufferPointer,
                                                                                        sizeof(iGMASStationInBuffer));
            iGMASStationSharedBuffer = (iGMASDataCenterSharedBufferPointer == 0) ? 0 : new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                                                                        SharedBuffer::ONLY_WRITE,
                                                                                        iGMASDataCenterSharedBufferPointer,
                                                                                        sizeof(iGMASDataCenterInBuffer));
            break;
    }
    otherCenterSharedBuffer = (otherCenterSharedBufferPointer == 0) ? 0 : new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                                                                     SharedBuffer::ONLY_WRITE,
                                                                                     otherCenterSharedBufferPointer,
                                                                                     sizeof(OtherCenterInBuffer));

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
                getIGMASStationsFromDOM();
                getIGMASDataCentersFromDOM();
                break;
        }
        getOtherCentersFromDOM();
        writeSharedBuffer();
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
            setIGMASStationsToDOM();
            setIGMASDataCentersToDOM();
            break;
    }
    setOtherCentersToDOM();

    writeConfigFile();
    writeSharedBuffer();
}

void ConfigHelper::clearReceiverMemID(int memID)
{
    receiverMemIDArray.clearBit(memID - RECEIVER_MEMID_START_INDEX);
}

void ConfigHelper::clearIGMASStationMemID(int memID)
{
    iGMASStationMemIDArray.clearBit(memID - IGMASSTATION_MEMID_START_INDEX);
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

            if (receiver->getMemID() == -1) {
                receiver->setMemID(findFreeReceiverMemID());
            }
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
            receiverNode.lastChild().appendChild(root.createTextNode(QString::number(receiver->getLongitude())));

            receiverNode.appendChild(root.createElement("LATITUDE"));
            receiverNode.lastChild().appendChild(root.createTextNode(QString::number(receiver->getLatitude())));

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

void ConfigHelper::getIGMASStationsFromDOM()
{
    QDomNode stationRoot = root.namedItem("BDLSS").namedItem("STATIONS");
    for (QDomNode stationNode = stationRoot.firstChild(); !stationNode.isNull(); stationNode = stationNode.nextSibling()) {
        iGMASStation* station = new iGMASStation();
        station->setStationName(stationNode.namedItem("STATIONNAME").toElement().text());
        station->setMountPoint(stationNode.namedItem("MOUNTPOINT").toElement().text());
        station->setMemID(stationNode.namedItem("MEMID").toElement().text());
        station->setLongitude(stationNode.namedItem("LONGITUDE").toElement().text());
        station->setLatitude(stationNode.namedItem("LATITUDE").toElement().text());
        station->setHeight(stationNode.namedItem("HEIGHT").toElement().text());
        station->setDetail(stationNode.namedItem("DETAIL").toElement().text());
        iGMASStationMemIDArray.setBit(station->getMemID() - IGMASSTATION_MEMID_START_INDEX);
        iGMASStations << station;
    }
}

void ConfigHelper::setIGMASStationsToDOM()
{
    QDomElement stationRoot = root.createElement("STATIONS");
    for (int i = 0; i < iGMASStations.size(); i++) {
        iGMASStation* station = iGMASStations[i];
        QDomElement stationNode = root.createElement("STATION");

        stationNode.appendChild(root.createElement("STATIONNAME"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getStationName()));

        stationNode.appendChild(root.createElement("MOUNTPOINT"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getMountPoint()));

        if (station->getMemID() == -1) {
            station->setMemID(findFreeIGMASStationMemID());
        }
        stationNode.appendChild(root.createElement("MEMID"));
        stationNode.lastChild().appendChild(root.createTextNode(QString::number(station->getMemID())));

        stationNode.appendChild(root.createElement("LONGITUDE"));
        stationNode.lastChild().appendChild(root.createTextNode(QString::number(station->getLongitude())));

        stationNode.appendChild(root.createElement("LATITUDE"));
        stationNode.lastChild().appendChild(root.createTextNode(QString::number(station->getLatitude())));

        stationNode.appendChild(root.createElement("HEIGHT"));
        stationNode.lastChild().appendChild(root.createTextNode(QString::number(station->getHeight())));

        stationNode.appendChild(root.createElement("DETAIL"));
        stationNode.lastChild().appendChild(root.createTextNode(station->getDetail()));

        stationRoot.appendChild(stationNode);
    }
    root.namedItem("BDLSS").appendChild(stationRoot);
}

void ConfigHelper::getIGMASDataCentersFromDOM()
{
    QDomNode centerRoot = root.namedItem("BDLSS").namedItem("DATACENTERS");
    for (QDomNode centerNode = centerRoot.firstChild(); !centerNode.isNull(); centerNode = centerNode.nextSibling()) {
        iGMASDataCenter* center = new iGMASDataCenter();
        center->setCenterName(centerNode.namedItem("CENTERNAME").toElement().text());
        center->setMasterIPAddress(centerNode.namedItem("MASTERIP").toElement().text());
        center->setMasterPort(centerNode.namedItem("MASTERPORT").toElement().text());
        center->setSlaveIPAddress(centerNode.namedItem("SLAVEIP").toElement().text());
        center->setSlavePort(centerNode.namedItem("SLAVEPORT").toElement().text());
        center->setUsername(centerNode.namedItem("USERNAME").toElement().text());
        center->setPassword(centerNode.namedItem("PASSWORD").toElement().text());
        center->setCenterDetail(centerNode.namedItem("DETAIL").toElement().text());
        iGMASDataCenters << center;
    }
}

void ConfigHelper::setIGMASDataCentersToDOM()
{
    QDomElement centerRoot = root.createElement("DATACENTERS");
    for (int i = 0; i < iGMASDataCenters.size(); i++) {
        iGMASDataCenter* center = iGMASDataCenters[i];
        QDomElement centerNode = root.createElement("CENTER");

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
        center->setCenterName(centerNode.namedItem("CENTERNAME").toElement().text());
        center->setIpAddress(centerNode.namedItem("IPADDRESS").toElement().text());
        center->setPort(centerNode.namedItem("PORT").toElement().text());
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

        centerNode.appendChild(root.createElement("CENTERNAME"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getCenterName()));

        centerNode.appendChild(root.createElement("IPADDRESS"));
        centerNode.lastChild().appendChild(root.createTextNode(center->getIpAddress()));

        centerNode.appendChild(root.createElement("PORT"));
        centerNode.lastChild().appendChild(root.createTextNode(QString::number(center->getPort())));

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

void ConfigHelper::writeSharedBuffer()
{
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
        {
            int receiverCount = 0;
            for (int i = 0; i < standardStations.size(); i++) {
                receiverCount += standardStations[i]->getReceivers().size();
            }
            ReceiverInBuffer receiversInBuffer[receiverCount];
            for (int i = 0, index = 0; i < standardStations.size(); i++) {
                for (int j = 0; j < standardStations[i]->getReceivers().size(); j++) {
                    receiversInBuffer[index++] = standardStations[i]->getReceivers()[j]->toReceiverInBuffer();
                }
            }
            if (receiverSharedBuffer != 0) {
                receiverSharedBuffer->writeData(&receiversInBuffer, receiverCount);
            }
            break;
        }
        case DeploymentType::BJ_CENTER:
        {
            iGMASStationInBuffer stationsInBuffer[iGMASStations.size()];
            for (int i = 0; i < iGMASStations.size(); i++) {
                stationsInBuffer[i] = iGMASStations[i]->toIGMASStationInBuffer();
            }
            if (iGMASStationSharedBuffer != 0) {
                iGMASStationSharedBuffer->writeData(&stationsInBuffer, iGMASStations.size());
            }
            iGMASDataCenterInBuffer dataCentersInBuffer[iGMASDataCenters.size()];
            for (int i = 0; i < iGMASDataCenters.size(); i++) {
                dataCentersInBuffer[i] = iGMASDataCenters[i]->toIGMASDataCenterInBuffer();
            }
            if (iGMASDataCenterSharedBuffer != 0) {
                iGMASDataCenterSharedBuffer->writeData(&dataCentersInBuffer, iGMASDataCenters.size());
            }
            break;
        }
    }
    OtherCenterInBuffer otherCenter[otherCenters.size()];
    for (int i = 0; i < otherCenters.size(); i++) {
        otherCenter[i] = otherCenters[i]->toOtherCenterInBuffer();
    }
    if (otherCenterSharedBuffer != 0) {
        otherCenterSharedBuffer->writeData(&otherCenter, otherCenters.size());
    }
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

int ConfigHelper::findFreeIGMASStationMemID()
{
    for (int i = 0; i < IGMASSTATION_MAXITEMCOUNT; i++) {
        if (!iGMASStationMemIDArray[i]) {
            iGMASStationMemIDArray.setBit(i);
            return i + IGMASSTATION_MEMID_START_INDEX;
        }
    }
    qDebug() << "SMAMMainUI:" << "Do not find free igmas station memid";
    return -1;
}

ConfigHelper::ConfigHelper() {}

ConfigHelper::ConfigHelper(const ConfigHelper&) {}

ConfigHelper&ConfigHelper::operator=(const ConfigHelper&) {}
