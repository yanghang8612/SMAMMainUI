#include <QPainter>

#include "harddrivenode.h"

HardDriveNode::HardDriveNode(quint8 length) :
    BaseNode(length)
{}

QRectF HardDriveNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length + 20, length + 20);
}

void HardDriveNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(":/hard_drive"));
}

