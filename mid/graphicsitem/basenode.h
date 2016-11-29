#ifndef BASENODE_H
#define BASENODE_H

#include <QGraphicsItem>

#include "edge.h"

class BaseNode : public QGraphicsItem
{
public:
	BaseNode();

    void addFromEdge(Edge* e);
    void addToEdge(Edge* e);
    void transformData();
	void setStatus(quint8 status);

protected:
    QList<Edge*> edgeFromNodeList;
    QList<Edge*> edgeToNodeList;
	quint8 status;
};

#endif // BASENODE_H
