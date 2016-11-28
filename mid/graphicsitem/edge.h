#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QObject>
#include <QQueue>

class BaseNode;

class Edge : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	Edge(BaseNode* sourceNode, BaseNode* destNode);
	void addData();

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

public slots:
	void adjust();

private:
	BaseNode* sourceNode;
	BaseNode* destNode;
	QPointF sourcePoint;
	QPointF destPoint;
	QPointF dataFlowOffset;

	QQueue<QPointF> dataList;
};

#endif // EDGE_H
