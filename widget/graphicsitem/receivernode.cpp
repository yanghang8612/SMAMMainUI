#include <QtGlobal>
#include <QPainter>
#include <QTimer>
#include <QTime>

#include "receivernode.h"
#include "edge.h"

ReceiverNode::ReceiverNode(Receiver* receiver, quint8 length) :
    BaseNode(length),
	receiver(receiver)
{
    formattedReceiverName = receiver->getReceiverName();
    quint8 lineCount = formattedReceiverName.length() / 5 + formattedReceiverName.length() % 5 == 0 ? 0 : 1;
    for (int i = 1; i <= lineCount; i++) {
        formattedReceiverName.insert(i * 5, '\n');
    }

//    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(doSomething()), Qt::QueuedConnection);
//    int r = qrand() % 5;
    //    timer->start((r + 5) * 1000);
}

QString ReceiverNode::getReceiverIPAddress() const
{
    return receiver->getIpAddress();
}

QRectF ReceiverNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length, length);
}

void ReceiverNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QString imageName;
    switch (status) {
        case 0:
            imageName = ":/receiver_normal";
            break;
        case 1:
            imageName = ":/receiver_green";
            break;
        case 2:
            imageName = ":/receiver_red";
            break;
        default:
            break;
    }
    painter->drawImage(QRectF(- length / 2, - length / 2, length, length), QImage(imageName));
    painter->setFont(QFont("Helvetica", 7, QFont::Bold));
    QTextOption option(Qt::AlignTrailing | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);
    painter->drawText(QRectF(- length / 2 - 40, - length / 2, 40, 40), formattedReceiverName, option);
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

