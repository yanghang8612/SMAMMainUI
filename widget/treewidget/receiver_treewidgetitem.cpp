#include "receiver_treewidgetitem.h"

ReceiverTreeWidgetItem::ReceiverTreeWidgetItem(Receiver* receiver, QTreeWidgetItem* parent) :
	QTreeWidgetItem(parent, 2),
	receiver(receiver), parent(parent)
{
	this->setText(0, receiver->getReceiverName());
}

ReceiverTreeWidgetItem::~ReceiverTreeWidgetItem()
{
	delete receiver;
}

