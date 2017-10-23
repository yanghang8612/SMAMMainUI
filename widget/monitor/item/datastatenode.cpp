#include <QPainter>
#include <QTimer>

#include "datastatenode.h"

DataStateNode::DataStateNode() :
    brushColor(Qt::white)
{}

void DataStateNode::flickerOnce()
{
    preBrushColor = brushColor;
    brushColor = Qt::white;
    update();
    QTimer::singleShot(80, this, SLOT(turnIntoNormal()));
}

void DataStateNode::setState(int state)
{
    switch (state) {
        case 0:
            brushColor = Qt::white;
            break;
        case 1:
            brushColor = Qt::green;
            break;
        case -1:
            brushColor = Qt::red;
    }
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
    brushColor = preBrushColor;
    update();
}
