#include <QPainter>

#include "igmasnode.h"

IGMASNode::IGMASNode(IGMASStation* station, quint8 length) :
    BaseNode(length),
    station(station)
{}

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
            imageName = ":/station_red";
            break;
        default:
            break;
    }
    painter->drawImage(QRectF(- length / 2, - length / 2, length, length), QImage(imageName));
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(- length / 2 - 10, length / 2 + 2, length + 20, 15, Qt::AlignCenter, station->getMount());
}

