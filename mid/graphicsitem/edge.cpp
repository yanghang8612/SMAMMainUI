#include <QPainter>
#include <QDebug>
#include <QTimer>

#include "edge.h"
#include "basenode.h"

Edge::Edge(BaseNode* sourceNode, BaseNode* destNode) :
    sourceNode(sourceNode), destNode(destNode),
    timer(0)
{
    sourceNode->addFromEdge(this);
    destNode->addToEdge(this);

    adjust();
}

void Edge::addData()
{
    if (0 == timer) {
        QTimer* timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(doSomething()), Qt::QueuedConnection);
        timer->start(5);
    }
	dataList << sourcePoint;
}

void Edge::adjust()
{
    QLineF line(mapFromItem(sourceNode, 0, 0), mapFromItem(destNode, 0, 0));
	qreal length = line.length();

    dataFlowOffset = QPointF((line.dx() * 5) / length, (line.dy() * 5) / length);

    prepareGeometryChange();

	qreal sourceWidth = sourceNode->boundingRect().width() / 2;
	QPointF sourceEdgeOffset((line.dx() * sourceWidth) / length, (line.dy() * sourceWidth) / length);
	sourcePoint = line.p1() + sourceEdgeOffset;

	qreal destWidth = destNode->boundingRect().width() / 2;
	QPointF destEdgeOffset((line.dx() * destWidth) / length, (line.dy() * destWidth) / length);
    destPoint = line.p2() - destEdgeOffset;
}

QRectF Edge::boundingRect() const
{
    return QRectF(sourcePoint + QPointF(-5, -5), QSizeF(destPoint.x() - sourcePoint.x() + 10, destPoint.y() - sourcePoint.y() + 10));
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(QLineF(sourcePoint, destPoint));

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::gray);
    int dataCount = dataList.size();
    if (0 == dataCount && 0 != timer) {
        timer->stop();
        delete timer;
        timer = 0;
    }
	for (int i = 0; i < dataCount; i++) {
        QPointF currentData = dataList.dequeue();
        painter->drawEllipse(currentData, 6, 6);
		currentData += dataFlowOffset;
        if (currentData.x() >= destPoint.x()) {
            destNode->transformData();
            continue;
        }
		dataList << currentData;
	}
}

void Edge::doSomething()
{
    update();
}

