#include <QPainter>

#include "common.h"
#include "maincenternode.h"

extern DeploymentType::Value deploymentType;

MainCenterNode::MainCenterNode(MainCenter* center, quint8 length) :
    BaseNode(length),
    center(center)
{}

QRectF MainCenterNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length + 40, length + 40);
}

void MainCenterNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(-length / 2, - length / 2 - 10, length, length), QImage(":/maincenter"));
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(-length / 2 - 10, length / 2 - 5, length + 20, 13, Qt::AlignCenter, center->getCenterName());
}
