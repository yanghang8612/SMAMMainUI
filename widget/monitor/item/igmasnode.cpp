#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>

#include "igmasnode.h"
#include "main_component_header.h"
#include "utilities/config_helper.h"

iGMASNode::iGMASNode(iGMASStation* station, quint8 length, QWidget* parent) :
    BaseNode(length),
    isConnected(false), station(station),
    stateNode(new DataStateNode()), stateWidget(new DataTransferStateFrame(parent))
{
    stateNode->setParentItem(this);
    stateNode->setPos(- length / 2, - length / 2);
    stateWidget->hide();
    registerSignalListener(this, "connected(int, int, bool)", "dataCenterConnected(int, int, bool)");
    registerSignalListener(this, "disconnected(int)", "dataCenterDisconnected(int)");
    registerSignalListener(this, "receivedData(int)", "dataCenterReceivedData(int)");
}

QRectF iGMASNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length, length);
}

void iGMASNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(- length / 2, - length / 2, length, length), QImage(":/igmas_node"));
    painter->setFont(QFont("Helvetica", 7 + (length / 20)));
    painter->drawText(- length / 2 - 10, length / 2 + 2, length + 20, 15, Qt::AlignCenter, station->getStationName());
}

void iGMASNode::connected(int memID, int centerID, bool isMaster)
{
    if (memID == station->getMemID()) {
        isConnected = true;
        setAcceptHoverEvents(true);
        stateNode->setState(1);
        stateWidget->setState(ConfigHelper::getIGMASDataCenterByCenterID(centerID)->getCenterName(), isMaster);
    }
}

void iGMASNode::disconnected(int memID)
{
    if (memID == station->getMemID()) {
        isConnected = false;
        setAcceptHoverEvents(false);
        stateNode->setState(0);
    }
}

void iGMASNode::receivedData(int memID)
{
    if (memID == station->getMemID()) {
        stateNode->flickerOnce();
    }
}

void iGMASNode::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    stateWidget->setGeometry(this->pos().x() + 620, this->pos().y() + 260, 170, 30);
    stateWidget->show();
}

void iGMASNode::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    stateWidget->hide();
    scene()->update();
}

