#ifndef DMZNODE_H
#define DMZNODE_H

#include "basenode.h"

class DMZNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    DMZNode(quint8 length);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

protected:
    void timerEvent(QTimerEvent* event);
};

#endif // DMZNODE_H
