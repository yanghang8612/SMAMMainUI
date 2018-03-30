#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include "edge.h"

#include "basenode.h"

Edge::Edge(BaseNode* sourceNode, BaseNode* destNode) :
    sourceNode(sourceNode), destNode(destNode)
{
    sourceNode->addFromEdge(this);
    destNode->addToEdge(this);

    QLineF line(mapFromItem(sourceNode, 0, 0), mapFromItem(destNode, 0, 0));
    qreal length = line.length();

    qreal sourceWidth = sourceNode->boundingRect().width() / 2;
    QPointF sourceEdgeOffset((line.dx() * sourceWidth) / length, (line.dy() * sourceWidth) / length);
    sourcePoint = line.p1() + sourceEdgeOffset;

    qreal destWidth = destNode->boundingRect().width() / 2;
    QPointF destEdgeOffset((line.dx() * destWidth) / length, (line.dy() * destWidth) / length);
    destPoint = line.p2() - destEdgeOffset;
}

QRectF Edge::boundingRect() const
{
    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(), destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-3, -3, 3, 3);
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(QLineF(sourcePoint, destPoint));
}
