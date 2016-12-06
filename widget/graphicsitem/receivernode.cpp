#include <QtGlobal>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QDebug>

#include "receivernode.h"
#include "edge.h"

ReceiverNode::ReceiverNode(Receiver* receiver) :
	receiver(receiver)
{
    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(doSomething()), Qt::QueuedConnection);
    int r = qrand() % 5;
    qDebug() << r;
    timer->start((r + 5) * 1000);
}

QRectF ReceiverNode::boundingRect() const
{
	return QRectF(-30, -30, 60, 60);
}

void ReceiverNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	QString imageName;
	if (0 == status) {
		imageName = ":/receiver_normal";
	}
	else if (1 == status) {
        imageName = ":/receiver_green";
	}
	else if (2 == status) {
		imageName = ":/receiver_red";
	}
    painter->drawImage(QRectF(-30, -30, 60, 60), QImage(imageName));
    painter->setFont(QFont("Helvetica", 8, QFont::Bold));
    painter->drawText(-50, 35, 100, 10, Qt::AlignCenter, receiver->getReceiverName());
}

void ReceiverNode::doSomething()
{
    if (getStatus() == 2) {
        timer->stop();
        delete timer;
        timer = 0;
    }
    else {
        foreach (Edge* edge, edgeFromNodeList) {
            //edge->adjust();
            edge->addData();
        }
    }
}

