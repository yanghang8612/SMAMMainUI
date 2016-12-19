#include "basenode.h"
#include "edge.h"

BaseNode::BaseNode(quint8 length) :
    length(length)
{

}

void BaseNode::addFromEdge(Edge* e)
{
    edgeFromNodeList << e;
}

void BaseNode::addToEdge(Edge* e)
{
    edgeToNodeList << e;
}

void BaseNode::transformData()
{
    foreach (Edge* edge, edgeFromNodeList) {
        edge->addData();
    }
}

void BaseNode::setStatus(quint8 status)
{
	this->status = status;
    prepareGeometryChange();
    update();
}

quint8 BaseNode::getStatus() const
{
    return status;
}



