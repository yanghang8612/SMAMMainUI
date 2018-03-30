#include <QPainter>

#include "terminalnode.h"

TerminalNode::TerminalNode(quint8 length) :
    BaseNode(length)
{}

QRectF TerminalNode::boundingRect() const
{
    return QRectF(-length / 2, -length / 2, length + 30, length + 30);
}

void TerminalNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(-length / 2, -length / 2 - 10, length, length), QImage(":/terminal"));
    painter->setFont(QFont("Helvetica", 8));
    painter->drawText(-length / 2 - 10, length / 2 - 5, length + 20, 13, Qt::AlignCenter, tr("用户终端"));

}
