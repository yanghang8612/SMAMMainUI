#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>

#include "monitornode.h"
#include "main_component_header.h"
#include "utilities/config_helper.h"

MonitorNode::MonitorNode(MonitorStation* station, quint8 length, DataTransferStateFrame* stateWidget, QWidget* parent) :
    BaseNode(length),
    isUsingStateWidget(false), isConnected(false),
    station(station), stateWidget(stateWidget)
{
    stationName = station->getStationName();
    stateNode = new DataStateNode(parent);
    stateNode->show();
    //stateNode->setPos(- length / 2, - length / 2);
    registerSignalSender(this);
    registerSignalListener(this, "connected(int, int, bool)", "dataCenterConnected(int, int, bool)");
    registerSignalListener(this, "disconnected(int)", "dataCenterDisconnected(int)");
    registerSignalListener(this, "receivedData(int, long)", "dataCenterReceivedData(int, long)");
    registerSignalListener(this, "handleNoData(int)", "dataCenterLongTimeNoData(int)");
}

MonitorNode::~MonitorNode()
{
    delete stateNode;
    removeSignalSender(this);
    removeSignaleListener(this);
}

QRectF MonitorNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length, length);
}

void MonitorNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(- length / 2, - length / 2, length, length), QImage(":/monitor_node"));
    painter->setFont(QFont("Helvetica", 7 + (length / 20)));
    painter->drawText(- length / 2 - 10, length / 2 + 2, length + 20, 15, Qt::AlignCenter, stationName);
}

MonitorStation* MonitorNode::getStation() const
{
    return station;
}

void MonitorNode::updateStateNode()
{
    stateNode->setGeometry(490 + this->pos().x() - length / 2 - 1, 205 + this->pos().y() - length / 2 - 1, 8, 8);
}

void MonitorNode::connected(int memID, int centerID, bool isMaster)
{
    if (memID == station->getMemID()) {
        isConnected = true;
        this->centerID = centerID;
        this->isMaster = isMaster;
        setAcceptHoverEvents(true);
        stateNode->setState(1);
        station->setState(MonitorStation::CONNECTED);
        emit stationStateChanged(station->getMemID());
    }
}

void MonitorNode::disconnected(int memID)
{
    if (memID == station->getMemID()) {
        isConnected = false;
        setAcceptHoverEvents(false);
        stateNode->setState(0);
        station->setState(MonitorStation::UNCONNECTED);
        emit stationStateChanged(station->getMemID());
    }
}

void MonitorNode::receivedData(int memID, long length)
{
    if (memID == station->getMemID()) {
        rcvdDataLength = length;
        if (isUsingStateWidget) {
            stateWidget->setRcvdDataLength(length);
        }
        stateNode->setState(1);
        stateNode->flickerOnce();
        if (MonitorStation::NORMAl != station->getState()) {
            station->setState(MonitorStation::NORMAl);
            emit stationStateChanged(station->getMemID());
        }
    }
}

void MonitorNode::handleNoData(int memID)
{
    if (memID == station->getMemID()) {
        stateNode->setState(2);
        if (MonitorStation::NODATA != station->getState()) {
            station->setState(MonitorStation::NODATA);
            emit stationStateChanged(station->getMemID());
        }
    }
}

void MonitorNode::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    isUsingStateWidget = true;
    stateWidget->setCurrentDataCenter(ConfigHelper::getDataCenterByCenterID(centerID)->getCenterName(), isMaster);
    stateWidget->setRcvdDataLength(rcvdDataLength);
    stateWidget->show();
}

void MonitorNode::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    isUsingStateWidget = false;
    stateWidget->hide();
}



