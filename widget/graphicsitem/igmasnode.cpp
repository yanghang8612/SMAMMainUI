#include <QPainter>

#include "igmasnode.h"
#include "common.h"
#include "main_component_header.h"

IGMASNode::IGMASNode(IGMASStation* station, quint8 length) :
    BaseNode(length),
    station(station), dataReceivingSharedBuffer(0)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkDataReceivingState()), Qt::QueuedConnection);
    timer->start(IGMAS_DATA_RECEIVING_STATE_CHECK_TIMEINTERVAL);
}

QString IGMASNode::getStationIPAddress() const
{
    return station->getIpAddress();
}

QRectF IGMASNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length, length);
}

void IGMASNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QString imageName;
    switch (status) {
        case 0:
            imageName = ":/station_normal";
            break;
        case 1:
            imageName = ":/station_green";
            break;
        case 2:
            imageName = ":/station_normal";
            break;
        default:
            break;
    }
    painter->drawImage(QRectF(- length / 2, - length / 2, length, length), QImage(imageName));
    painter->setFont(QFont("Helvetica", 7 + (length / 20)));
    painter->drawText(- length / 2 - 10, length / 2 + 2, length + 20, 15, Qt::AlignCenter, station->getMount());
}

void IGMASNode::checkDataReceivingState()
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

