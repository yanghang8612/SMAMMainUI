#include <QPainter>
#include <QTimer>

#include "datastatenode.h"

DataStateNode::DataStateNode() :
    brushColor(Qt::white)
{}

void DataStateNode::flickerOnce()
{
    brushColor = Qt::green;
    update();
    QTimer::singleShot(500, this, SLOT(turnIntoNormal()));
}

QRectF DataStateNode::boundingRect() const
{
    return QRectF(-2.5, -2.5, 5, 5);
}

void DataStateNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::gray);
    painter->setBrush(brushColor);
    painter->drawEllipse(-2.5, -2.5, 5, 5);
}

void DataStateNode::turnIntoNormal()
{
    brushColor = Qt::white;
    update();
}

