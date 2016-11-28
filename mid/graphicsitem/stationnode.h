#ifndef STATIONNODE_H
#define STATIONNODE_H

#include "basenode.h"
#include "station/standard_station.h"

class StationNode : public BaseNode
{
public:
	StationNode(StandardStation* station);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
	StandardStation* station;
};

#endif // STATIONNODE_H
