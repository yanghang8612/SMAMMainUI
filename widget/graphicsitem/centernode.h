#ifndef CENTERNODE_H
#define CENTERNODE_H

#include "basenode.h"

class CenterNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    CenterNode();

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};

#endif // CENTERNODE_H
