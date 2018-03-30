#include <QtGlobal>
#include <QPainter>
#include <QTimer>
#include <QTime>

#include "receivernode.h"

ReceiverNode::ReceiverNode(Receiver* receiver, quint8 length) :
    BaseNode(length),
	receiver(receiver)
{
    formattedReceiverName = receiver->getReceiverName();
    quint8 lineCount = formattedReceiverName.length() / 5 + formattedReceiverName.length() % 5 == 0 ? 0 : 1;
    for (int i = 1; i <= lineCount; i++) {
        formattedReceiverName.insert(i * 5, '\n');
    }
}

QRectF ReceiverNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length, length);
}

void ReceiverNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(- length / 2, - length / 2, length, length), QImage(":/receiver_normal"));
    painter->setFont(QFont("Helvetica", 7, QFont::Bold));
    QTextOption option(Qt::AlignTrailing | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);
    painter->drawText(QRectF(- length / 2 - 40, - length / 2, 40, 40), formattedReceiverName, option);
}

