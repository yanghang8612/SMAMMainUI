#include <QPainter>

#include "dmznode.h"
#include "common.h"

extern DeploymentType::Value deploymentType;
extern void* DMZSharedBufferPointer;

DMZNode::DMZNode(quint8 length) :
    BaseNode(length)
{
    if (deploymentType == DeploymentType::XJ_CENTER) {
        startTimer(500);
    }
}

QRectF DMZNode::boundingRect() const
{
    return QRectF(-length / 2, -length / 2, length + 30, length + 30);
}

void DMZNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QString imageName;
    switch (status) {
        case 0:
            imageName = ":/dmz_normal";
            break;
        case 1:
            imageName = ":/dmz_green";
            break;
        case 2:
            imageName = ":/dmz_red";
            break;
        default:
            break;
    }
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(imageName));
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(-length / 2 - 10, length / 2 - 5, length + 20, 13, Qt::AlignCenter, "DMZ区");
}

void DMZNode::timerEvent(QTimerEvent*)
{
    if (DMZSharedBufferPointer != 0 && *((bool*) DMZSharedBufferPointer)) {
        setStatus(1);
        foreach (Edge* edge, edgeToNodeList) {
            edge->setStatus(1);
        }
    }
    else {
        setStatus(2);
        foreach (Edge* edge, edgeToNodeList) {
            edge->setStatus(2);
        }
    }
}
