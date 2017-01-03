#ifndef STATIONNODE_H
#define STATIONNODE_H

#include "basenode.h"
#include "bean/station/standard_station.h"

class StationNode : public BaseNode
{
public:
    StationNode(StandardStation* station, quint8 length);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
	StandardStation* station;
};

#endif // STATIONNODE_H
