#ifndef USERSNODE_H
#define USERSNODE_H

#include "basenode.h"

class TerminalNode :public QObject, public BaseNode
{
    Q_OBJECT

public:
    TerminalNode(quint8 length);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};

#endif // USERSNODE_H
