#include "basenode.h"

#include "edge.h"

BaseNode::BaseNode(quint8 length) :
    length(length)
{}

void BaseNode::addFromEdge(Edge* e)
{
    edgeFromNodeList << e;
}

void BaseNode::addToEdge(Edge* e)
{
    edgeToNodeList << e;
}



