#include <QPainter>

#include "stationnode.h"

StationNode::StationNode(StandardStation* station, quint8 length) :
    BaseNode(length),
	station(station)
{

}

QRectF StationNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length, length);
}

void StationNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
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
    painter->drawText(- length / 2 - 10, length / 2 + 2, length + 20, 10, Qt::AlignCenter, station->getStationName());
    painter->setPen(QPen(Qt::black,4));
    painter->drawRect(QRectF(length / 2, - length / 2, length * 2, length * 2));
}
