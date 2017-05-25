#include <QPainter>

#include "standardnode.h"

StandardNode::StandardNode(StandardStation* station, quint8 length) :
    BaseNode(length),
	station(station)
{}

QRectF StandardNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length, length);
}

void StandardNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
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
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(- length / 2 - 10, length / 2 + 2, length + 20, 15, Qt::AlignCenter, station->getStationName());
    painter->setPen(QPen(Qt::black,2));
    painter->drawRect(QRectF(- length / 2 - length * 3 - 5, - length / 2, length * 3, length));
}
