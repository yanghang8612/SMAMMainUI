#ifndef CENTERNODE_H
#define CENTERNODE_H

#include "basenode.h"
#include "bean/center/base_center.h"

class CenterNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    CenterNode(BaseCenter* center, quint8 length);

    QString getCenterIPAddress() const;
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

protected:
    void timerEvent(QTimerEvent*);

private:
    BaseCenter* center;
};

#endif // CENTERNODE_H
