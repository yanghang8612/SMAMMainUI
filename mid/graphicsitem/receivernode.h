#ifndef RECEIVERNODE_H
#define RECEIVERNODE_H

#include "basenode.h"
#include "station/receiver.h"

class ReceiverNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
	ReceiverNode(Receiver* receiver);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private slots:
    void doSomething();

private:
	Receiver* receiver;
};

#endif // RECEIVERNODE_H
