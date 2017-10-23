#include <QPainter>

#include "usersnode.h"

extern void* userRealtimeInfoSharedBufferPointer;

UsersNode::UsersNode(quint8 length) :
    BaseNode(length)
{
    startTimer(500);
}

QRectF UsersNode::boundingRect() const
{
    return QRectF(-length / 2, -length / 2, length + 30, length + 30);
}

void UsersNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    //painter->setRenderHint(QPainter::Antialiasing);
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(":/users"));
    painter->setFont(QFont("Helvetica", 8));
    painter->drawText(-length / 2 - 10, length / 2, length + 20, 13, Qt::AlignCenter, tr("用户终端"));

}

void UsersNode::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    if (userRealtimeInfoSharedBufferPointer != 0 && (*((int*) userRealtimeInfoSharedBufferPointer)) > 0) {
        setStatus(1);
        foreach (Edge* edge, edgeToNodeList) {
            edge->setStatus(1);
        }
    }
    else {
        setStatus(2);
        foreach (Edge* edge, edgeToNodeList) {
            edge->setStatus(2);
        }
    }
}
