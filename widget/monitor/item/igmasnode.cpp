#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>

#include "igmasnode.h"
#include "common.h"
#include "main_component_header.h"

iGMASNode::iGMASNode(iGMASStation* station, quint8 length, QWidget* parent) :
    BaseNode(length),
    station(station), stateNode(new DataStateNode()), stateWidget(new DataTransferStateFrame(parent)),
    dataReceivingSharedBuffer(0)
{
    stateNode->setParentItem(this);
    stateNode->setPos(- length / 2, - length / 2);
    stateWidget->hide();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkDataReceivingState()), Qt::QueuedConnection);
    timer->start(IGMAS_DATA_RECEIVING_STATE_CHECK_TIMEINTERVAL);

    setAcceptHoverEvents(true);
}

QString iGMASNode::getStationIPAddress() const
{
    return station->getStationName();
}

QRectF iGMASNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length, length);
}

void iGMASNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
//    switch (status) {
//        case 0:
//            imageName = ":/igmas_node";
//            break;
//        case 1:
//            imageName = ":/igmas_station";
//            break;
//        case 2:
//            imageName = ":/igmas_station";
//            break;
//        default:
//            break;
//    }
    painter->drawImage(QRectF(- length / 2, - length / 2, length, length), QImage(":/igmas_node"));
    painter->setFont(QFont("Helvetica", 7 + (length / 20)));
    painter->drawText(- length / 2 - 10, length / 2 + 2, length + 20, 15, Qt::AlignCenter, station->getStationName());
}

void iGMASNode::checkDataReceivingState()
{
    if (getStatus() == 1) {
        if (dataReceivingSharedBuffer == 0) {
            void* pointer = FindMemoryInfoFunc(station->getMemID(), 4096 + 80);
            dataReceivingSharedBuffer = new SharedBuffer(SharedBuffer::LOOP_BUFFER, SharedBuffer::ONLY_READ, pointer);
        }
        else {
            if (dataReceivingSharedBuffer->getDataWriteState()) {
                foreach (Edge* edge, edgeFromNodeList) {
                    //edge->adjust();
                    edge->setStatus(1);
                }
            }
            else {
                foreach (Edge* edge, edgeFromNodeList) {
                    //edge->adjust();
                    edge->setStatus(2);
                }
            }
        }
    }
}

void iGMASNode::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    stateWidget->setGeometry(this->pos().x() + 300, this->pos().y() + 50, 160, 200);
    stateWidget->show();
}

void iGMASNode::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    qDebug() << "bisha";
    stateWidget->hide();
    scene()->update();
}

