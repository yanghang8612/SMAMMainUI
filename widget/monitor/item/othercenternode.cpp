#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>

#include "othercenternode.h"
#include "common.h"
#include "main_component_header.h"

OtherCenterNode::OtherCenterNode(OtherCenter* center, quint8 length, QWidget* parent) :
    BaseNode(length),
    center(center)
{
    centerName = center->getCenterName();
    stateNode = new DataStateNode(parent);
    stateNode->setState(1);
    stateNode->show();
    registerSignalListener(this, "connected(int)", "otherCenterConnected(int)");
    registerSignalListener(this, "disconnected(int)", "otherCenterDisconnected(int)");
}

OtherCenterNode::~OtherCenterNode()
{
    delete stateNode;
    removeSignaleListener(this);
}

QRectF OtherCenterNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length + 40, length + 40);
}

void OtherCenterNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(-length / 2, - length / 2 - 10, length, length), QImage(":/othercenter_node"));
    painter->setFont(QFont("Helvetica", 8));
    painter->drawText(-length / 2 - 25, length / 2 - 5, length + 50, 13, Qt::AlignCenter, centerName);
}

OtherCenter* OtherCenterNode::getCenter() const
{
    return center;
}

void OtherCenterNode::updateStateNode()
{
    stateNode->setGeometry(490 + this->pos().x() - length / 2 - 1, 205 + this->pos().y() - length / 2 - 1, 8, 8);
}

void OtherCenterNode::clearEdge()
{
    for (int i = 0; i < edgeToNodeList.size(); i++) {
        this->scene()->removeItem(edgeToNodeList[i]);
    }
    for (int i = 0; i < edgeFromNodeList.size(); i++) {
        this->scene()->removeItem(edgeFromNodeList[i]);
    }
    //this->scene()->update();
}

void OtherCenterNode::connected(int centerID)
{
    if (centerID == center->getCenterID()) {
        stateNode->setState(3);
    }
}

void OtherCenterNode::disconnected(int centerID)
{
    if (centerID == center->getCenterID()) {
        stateNode->setState(1);
    }
}


