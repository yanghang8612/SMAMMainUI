#ifndef FILENODE_H
#define FILENODE_H

#include "basenode.h"

class FileNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    FileNode(quint8 length);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};

#endif // FILENODE_H
