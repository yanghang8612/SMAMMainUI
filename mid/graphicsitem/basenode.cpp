#include "basenode.h"

BaseNode::BaseNode()
{

}

void BaseNode::addEdge(Edge* e)
{
	edgeList << e;
}

void BaseNode::setStatus(quint8 status)
{
	this->status = status;
}

