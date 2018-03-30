#include <QPainter>

#include "networknode.h"

NetworkNode::NetworkNode(quint8 length) : BaseNode(length)
{}

QRectF NetworkNode::boundingRect() const
{
    return QRectF(-length / 2, -length / 2, length + 30, length + 30);
}

void NetworkNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(":/network"));
    painter->setFont(QFont("Helvetica", 8));
    painter->drawText(-length / 2 - 10, length / 2 + 5, length + 30, 13, Qt::AlignCenter, tr("全球监测站网"));
}
