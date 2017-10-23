#include <QPainter>

#include "common.h"
#include "othercenternode.h"

extern DeploymentType::Value deploymentType;

OtherCenterNode::OtherCenterNode(OtherCenter* center, quint8 length) :
    BaseNode(length),
    center(center)
{}

QRectF OtherCenterNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length + 40, length + 40);
}

void OtherCenterNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(-length / 2, - length / 2 - 10, length, length), QImage(":/othercenter"));
    painter->setFont(QFont("Helvetica", 9));
    painter->drawText(-length / 2 - 10, length / 2 - 5, length + 20, 13, Qt::AlignCenter, center->getCenterName());
}

void OtherCenterNode::timerEvent(QTimerEvent*)
{}
