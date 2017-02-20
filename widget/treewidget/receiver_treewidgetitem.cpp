#include "receiver_treewidgetitem.h"

ReceiverTreeWidgetItem::ReceiverTreeWidgetItem(QTreeWidgetItem* parent, int type, Receiver* receiver) :
    QTreeWidgetItem(parent, type),
    receiver(receiver)
{
	this->setText(0, receiver->getReceiverName());
	this->setIcon(0, QIcon(":/standard_receiver"));
	this->setData(0, Qt::UserRole, QVariant::fromValue((void*) receiver));
}

ReceiverTreeWidgetItem::~ReceiverTreeWidgetItem()
{
	delete receiver;
}

