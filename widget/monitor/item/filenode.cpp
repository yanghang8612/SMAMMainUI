#include <QPainter>

#include "filenode.h"

FileNode::FileNode(quint8 length) :
    BaseNode(length)
{
    setStatus(1);
}

QRectF FileNode::boundingRect() const
{
    return QRectF(-length / 2, -length / 2, length + 30, length + 30);
}

void FileNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QString imageName;
    switch (status) {
        case 0:
            imageName = ":/saved_file_normal";
            break;
        case 1:
            imageName = ":/saved_file_green";
            break;
        case 2:
            imageName = ":/saved_file_normal";
            break;
        default:
            break;
    }
    painter->drawImage(QRectF(-length / 2, -length / 2, length, length), QImage(imageName));
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(-length / 2 - 10, length / 2 + 2, length + 20, 13, Qt::AlignCenter, "数据存储");
}
