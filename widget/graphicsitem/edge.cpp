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
    sourceNode(sourceNode), destNode(destNode),
    timer(0), status(0)
{
    sourceNode->addFromEdge(this);
    destNode->addToEdge(this);

    adjust();
}

void Edge::addData()
{
    if (0 == timer) {
//        QThread* timerThread = new QThread(this);
//        timerThread->start();

//        timer = new QTimer(0);
//        timer->setInterval(50);
//        timer->moveToThread(timerThread);
//        connect(timer, SIGNAL(timeout()), this, SLOT(doSomething()));
//        connect(timerThread, SIGNAL(started()), timer, SLOT(start()));

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(doSomething()));
        timer->start(10);
    }
    dataList << sourcePoint;

//    QGraphicsEllipseItem* ball = new QGraphicsEllipseItem(-5, -5, 10, 10, this, this->scene());
//    dataList << ball;
//    ball->setPos(sourcePoint);
//    ball->setPen(QPen(Qt::gray, 2));
//    ball->setBrush(Qt::green);

//    QTimeLine* timer = new QTimeLine(3000);

//    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
//    animation->setItem(ball);
//    animation->setTimeLine(timer);

//    QLineF line(sourcePoint, destPoint);
//    qreal length = line.length();
//    int steps = length / 3 + 1;
//    for (int i = 0; i < steps; i++) {
//        animation->setPosAt((qreal) i / steps, sourcePoint + i * dataFlowOffset);
//    }

//    connect(timer, SIGNAL(finished()), this, SLOT(finishAnimation()));
//    timer->start();
}

void Edge::adjust()
{
    QLineF line(mapFromItem(sourceNode, 0, 0), mapFromItem(destNode, 0, 0));
	qreal length = line.length();

    dataFlowOffset = QPointF((line.dx() * 3) / length, (line.dy() * 3) / length);

    prepareGeometryChange();

    qreal sourceWidth = sourceNode->boundingRect().width() / 2;
    QPointF sourceEdgeOffset((line.dx() * sourceWidth) / length, (line.dy() * sourceWidth) / length);
	sourcePoint = line.p1() + sourceEdgeOffset;

    qreal destWidth = destNode->boundingRect().width() / 2;
	QPointF destEdgeOffset((line.dx() * destWidth) / length, (line.dy() * destWidth) / length);
    destPoint = line.p2() - destEdgeOffset;
}
quint8 Edge::getStatus() const
{
    return status;
}

void Edge::setStatus(const quint8& value)
{
    status = value;
    prepareGeometryChange();
    update();
}


QRectF Edge::boundingRect() const
{
    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(), destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-3, -3, 3, 3);
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QBrush lineColor;
    switch (status) {
        case 0:
            lineColor = Qt::black;
            break;
        case 1:
            lineColor = Qt::darkGreen;
            break;
        case 2:
            lineColor = Qt::darkRed;
            break;
        default:
            break;
    }
    painter->setPen(QPen(lineColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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
        painter->drawEllipse(currentData, 4, 4);
        currentData += dataFlowOffset;
        if (QLineF(sourcePoint, currentData).length() >= QLineF(sourcePoint, destPoint).length()) {
            destNode->transformData();
            continue;
        }
        dataList << currentData;
    }
}

void Edge::doSomething()
{
    //qDebug() << sourcePoint.x() << timer->interval();
    prepareGeometryChange();
    update();
}

void Edge::finishAnimation()
{
//    QGraphicsItem* firstItem = dataList.dequeue();
//    this->scene()->removeItem(firstItem);
//    delete firstItem;
//    destNode->transformData();
}

