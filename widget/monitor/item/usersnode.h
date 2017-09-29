#ifndef USERSNODE_H
#define USERSNODE_H

#include "basenode.h"

class UsersNode :public QObject, public BaseNode
{
    Q_OBJECT

public:
    UsersNode(quint8 length);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

protected:
    void timerEvent(QTimerEvent* event);
};

#endif // USERSNODE_H
