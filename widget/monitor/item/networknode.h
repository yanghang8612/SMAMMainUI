#ifndef NETWORKNODE_H
#define NETWORKNODE_H

#include <QObject>

#include "basenode.h"

class NetworkNode : public QObject, public BaseNode
{
    Q_OBJECT
public:
    NetworkNode(quint8 length);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};

#endif // NETWORKNODE_H
