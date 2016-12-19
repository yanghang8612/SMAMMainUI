#include <QPainter>

#include "centernode.h"

CenterNode::CenterNode(quint8 length) :
    BaseNode(length)
{

}

QRectF CenterNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length + 20, length + 20);
}

void CenterNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(-length / 2, - length / 2, length, length), QImage(":/centre_normal"));
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(-length / 2 - 10, length / 2 + 2, length + 20, 15, Qt::AlignCenter, tr("新疆中心"));
}
