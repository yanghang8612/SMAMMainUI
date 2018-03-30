#ifndef BASENODE_H
#define BASENODE_H

#include <QGraphicsItem>

#include "edge.h"

class BaseNode : public QGraphicsItem
{
public:
    BaseNode(quint8 length);

    void addFromEdge(Edge* e);
    void addToEdge(Edge* e);

protected:
    QList<Edge*> edgeFromNodeList;
    QList<Edge*> edgeToNodeList;
    quint8 length;
};

#endif // BASENODE_H
