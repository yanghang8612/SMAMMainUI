#ifndef RECEIVERTREEWIDGETITEM_H
#define RECEIVERTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "bean/station/receiver.h"

class ReceiverTreeWidgetItem : public QTreeWidgetItem
{
public:
	ReceiverTreeWidgetItem(QTreeWidgetItem* parent = 0, Receiver* receiver = 0);
	~ReceiverTreeWidgetItem();

private:
	QTreeWidgetItem* parent;
	Receiver* receiver;
};

#endif // RECEIVERTREEWIDGETITEM_H
