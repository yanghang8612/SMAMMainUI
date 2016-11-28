#ifndef RECEIVERNODE_H
#define RECEIVERNODE_H

#include "basenode.h"
#include "station/receiver.h"

class ReceiverNode : public BaseNode
{
public:
	ReceiverNode(Receiver* receiver);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
	Receiver* receiver;
};

#endif // RECEIVERNODE_H
