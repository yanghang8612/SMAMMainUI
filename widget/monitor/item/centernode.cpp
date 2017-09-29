#include <QPainter>

#include "common.h"
#include "centernode.h"

extern DeploymentType::Value deploymentType;

CenterNode::CenterNode(OtherCenter* center, quint8 length) :
    BaseNode(length),
    center(center)
{
//    if (deploymentType == DeploymentType::XJ_DMZ) {
//        startTimer(500);
//    }
}

QString CenterNode::getCenterIPAddress() const
{
    return center->getIpAddress();
}

QRectF CenterNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length + 40, length + 40);
}

void CenterNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QString imageName;
    switch (status) {
        case 0:
            imageName = ":/center_normal";
            break;
        case 1:
            imageName = ":/center_green";
            break;
        case 2:
            imageName = ":/center_normal";
            break;
        default:
            break;
    }
    painter->drawImage(QRectF(-length / 2, - length / 2 - 10, length, length), QImage(imageName));
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(-length / 2 - 10, length / 2 - 5, length + 20, 13, Qt::AlignCenter, center->getCenterName());
}

void CenterNode::timerEvent(QTimerEvent*)
{
}
