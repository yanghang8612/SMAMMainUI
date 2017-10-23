#ifndef OTHERCENTERNODE_H
#define OTHERCENTERNODE_H

#include "basenode.h"
#include "bean/other_center.h"

class OtherCenterNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    OtherCenterNode(OtherCenter* center, quint8 length);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

protected:
    void timerEvent(QTimerEvent* event);

private:
    OtherCenter* center;
};

#endif // OTHERCENTERNODE_H
