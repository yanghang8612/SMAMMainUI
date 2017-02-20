#ifndef RECEIVERTREEWIDGETITEM_H
#define RECEIVERTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "bean/station/receiver.h"

class ReceiverTreeWidgetItem : public QTreeWidgetItem
{
public:
    ReceiverTreeWidgetItem(QTreeWidgetItem* parent, int type, Receiver* receiver);
	~ReceiverTreeWidgetItem();

private:
	Receiver* receiver;
};

#endif // RECEIVERTREEWIDGETITEM_H
