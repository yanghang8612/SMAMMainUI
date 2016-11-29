#include <QPainter>

#include "stationnode.h"

StationNode::StationNode(StandardStation* station) :
	station(station)
{

}

QRectF StationNode::boundingRect() const
{
	return QRectF(-40, -40, 80, 80);
}

void StationNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	QString imageName;
	if (0 == status) {
		imageName = ":/station_normal";
	}
	else if (1 == status) {
		imageName = ":/station_green";
	}
	else if (2 == status) {
		imageName = ":/station_red";
	}
	painter->drawImage(QRectF(-40, -40, 80, 80), QImage(imageName));
}
