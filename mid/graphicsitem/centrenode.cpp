#include <QPainter>

#include "centrenode.h"

CentreNode::CentreNode()
{

}

QRectF CentreNode::boundingRect() const
{
	return QRectF(-50, -50, 100, 100);
}

void CentreNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(QRectF(-50, -50, 100, 100), QImage(":/centre_normal"));
}
