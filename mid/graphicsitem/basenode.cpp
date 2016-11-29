﻿#include "basenode.h"
#include "edge.h"

BaseNode::BaseNode()
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
}

