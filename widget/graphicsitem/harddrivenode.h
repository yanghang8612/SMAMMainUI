#ifndef HARDDRIVENODE_H
#define HARDDRIVENODE_H

#include "basenode.h"


class HardDriveNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    HardDriveNode(quint8 length);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};

#endif // HARDDRIVENODE_H
