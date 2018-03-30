#include <QPainter>

#include "filenode.h"

FileNode::FileNode(quint8 length) : BaseNode(length)
{}

QRectF FileNode::boundingRect() const
{
    return QRectF(-length / 2, -length / 2, length + 30, length + 30);
}

void FileNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(":/saved_file"));
    painter->setFont(QFont("Helvetica", 8));
    painter->drawText(-length / 2 - 10, length / 2 + 5, length + 20, 13, Qt::AlignCenter, tr("数据存储"));
}
