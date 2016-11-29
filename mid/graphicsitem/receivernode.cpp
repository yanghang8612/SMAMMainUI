#include <QPainter>

#include "receivernode.h"

ReceiverNode::ReceiverNode(Receiver* receiver) :
	receiver(receiver)
{

}

QRectF ReceiverNode::boundingRect() const
{
	return QRectF(-30, -30, 60, 60);
}

void ReceiverNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	QString imageName;
	if (0 == status) {
		imageName = ":/receiver_normal";
	}
	else if (1 == status) {
		imageName = ":/receiver_green";
	}
	else if (2 == status) {
		imageName = ":/receiver_red";
	}
	painter->drawImage(QRectF(-30, -30, 60, 60), QImage(imageName));
}

