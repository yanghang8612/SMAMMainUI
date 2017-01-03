#include <QPainter>

#include "centernode.h"

CenterNode::CenterNode(quint8 length, const QString& centerName) :
    BaseNode(length),
    centerName(centerName)
{

}

QRectF CenterNode::boundingRect() const
{
    return QRectF(- length / 2, - length / 2, length + 40, length + 40);
}

void CenterNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QString imageName;
    switch (status) {
        case 0:
            imageName = ":/center_normal";
            break;
        case 1:
            imageName = ":/center_green";
            break;
        case 2:
            imageName = ":/center_red";
            break;
        default:
            break;
    }
    painter->drawImage(QRectF(-length / 2, - length / 2, length, length), QImage(imageName));
    painter->setFont(QFont("Helvetica", 10, QFont::Bold));
    painter->drawText(-length / 2 - 10, length / 2 + 2, length + 20, 15, Qt::AlignCenter, centerName);
}
