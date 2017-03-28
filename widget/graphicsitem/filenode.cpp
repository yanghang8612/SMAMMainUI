#include <QPainter>

#include "filenode.h"

FileNode::FileNode(quint8 length) :
    BaseNode(length)
{}

QRectF FileNode::boundingRect() const
{
    return QRectF(-length / 2, -length / 2, length + 20, length + 20);
}

void FileNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(":/saved_file"));
}
