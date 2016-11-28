#ifndef CENTRENODE_H
#define CENTRENODE_H

#include "basenode.h"

class CentreNode : public BaseNode
{
public:
	CentreNode();

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};

#endif // CENTRENODE_H
