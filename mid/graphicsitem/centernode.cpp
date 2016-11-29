#include <QPainter>

#include "centernode.h"

CentreNode::CentreNode()
{

}

QRectF CentreNode::boundingRect() const
{
	return QRectF(-50, -50, 100, 100);
}

void CentreNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	painter->drawImage(QRectF(-50, -50, 100, 100), QImage(":/centre_normal"));
    painter->setFont(QFont("Helvetica", 18, QFont::Bold));
    painter->drawText(-50, 60, 100, 20, Qt::AlignCenter, tr("北京中心"));
}
