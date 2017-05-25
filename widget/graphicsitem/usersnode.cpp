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
    QString imageName;
    switch (status) {
        case 0:
            imageName = ":/users_normal";
            break;
        case 1:
            imageName = ":/users_green";
            break;
        case 2:
            imageName = ":/users_normal";
            break;
        default:
            break;
    }
    //painter->setRenderHint(QPainter::Antialiasing);
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(imageName));
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(-length / 2 - 10, length / 2 - 5, length + 20, 13, Qt::AlignCenter, "用户终端");

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
