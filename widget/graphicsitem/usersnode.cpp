#include <QPainter>

#include "usersnode.h"

UsersNode::UsersNode(quint8 length) :
    BaseNode(length)
{

}

QRectF UsersNode::boundingRect() const
{
    return QRectF(-length / 2, -length / 2, length, length);
}

void UsersNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(":/users"));
}
