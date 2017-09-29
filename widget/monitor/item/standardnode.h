#ifndef STANDARDNODE_H
#define STANDARDNODE_H

#include "basenode.h"
#include "bean/standard_station.h"

class StandardNode : public BaseNode
{
public:
    StandardNode(StandardStation* station, quint8 length);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
	StandardStation* station;
};

#endif // STANDARDNODE_H
