#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QQueue>
#include <QTimer>

class BaseNode;

class Edge : public QGraphicsItem
{
public:
    Edge(BaseNode* sourceNode, BaseNode* destNode);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
	BaseNode* sourceNode;
	BaseNode* destNode;
	QPointF sourcePoint;
    QPointF destPoint;
};

#endif // EDGE_H
