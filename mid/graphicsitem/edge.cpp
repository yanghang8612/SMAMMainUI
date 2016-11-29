#include <QPainter>
#include <QDebug>
#include <QTimer>

#include "edge.h"
#include "basenode.h"

Edge::Edge(BaseNode* sourceNode, BaseNode* destNode) :
	sourceNode(sourceNode), destNode(destNode)
{
	sourceNode->addEdge(this);
	destNode->addEdge(this);
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(adjust()));
	timer->start(500);
}

void Edge::addData()
{
	qDebug() << sourcePoint.x() << sourcePoint.y();
	dataList << sourcePoint;
}

void Edge::adjust()
{
	QLineF line(mapFromItem(sourceNode, 0, 0), mapFromItem(destNode, 0, 0));
	qreal length = line.length();

	dataFlowOffset = QPointF((line.dx() * 10) / length, (line.dy() * 10) / length);

	qreal sourceWidth = sourceNode->boundingRect().width() / 2;
	QPointF sourceEdgeOffset((line.dx() * sourceWidth) / length, (line.dy() * sourceWidth) / length);
	sourcePoint = line.p1() + sourceEdgeOffset;

	qreal destWidth = destNode->boundingRect().width() / 2;
	QPointF destEdgeOffset((line.dx() * destWidth) / length, (line.dy() * destWidth) / length);
	destPoint = line.p2() - destEdgeOffset;

	update();
}

QRectF Edge::boundingRect() const
{
	return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(), destPoint.y() - sourcePoint.y()));
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	painter->setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->setBrush(Qt::green);
	int dataCount = dataList.size();
	qDebug() << "count:" << dataCount;
	for (int i = 0; i < dataCount; i++) {
		QPointF currentData = dataList.dequeue();
		qDebug() << currentData.x() << currentData.y();
		painter->drawEllipse(currentData, 5, 5);
		currentData += dataFlowOffset;
//		if (currentData.x() >= destPoint.x() || currentData.y() >= destPoint.y()) {
//			continue;
//		}
		dataList << currentData;
	}

	painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->drawLine(QLineF(sourcePoint, destPoint));
}

