#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QQueue>
#include <QTimer>

class BaseNode;

class Edge : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	Edge(BaseNode* sourceNode, BaseNode* destNode);
	void addData();

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    quint8 getStatus() const;
    Edge* setStatus(const quint8 &value);

private slots:
    void doSomething();
    void finishAnimation();

public slots:
	void adjust();

private:
	BaseNode* sourceNode;
	BaseNode* destNode;
	QPointF sourcePoint;
	QPointF destPoint;
	QPointF dataFlowOffset;

    QQueue<QPointF> dataList;
    //QQueue<QGraphicsItem*> dataList;
    QTimer* timer;

    quint8 status;
};

#endif // EDGE_H
