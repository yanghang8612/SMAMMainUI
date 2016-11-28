#ifndef BASENODE_H
#define BASENODE_H

#include <QGraphicsItem>

#include "edge.h"

class BaseNode : public QGraphicsItem
{
public:
	BaseNode();

	void addEdge(Edge* e);
	void setStatus(quint8 status);

protected:
	QList<Edge*> edgeList;
	quint8 status;
};

#endif // BASENODE_H
