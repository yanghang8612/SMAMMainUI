#ifndef RECEIVERTREEWIDGETITEM_H
#define RECEIVERTREEWIDGETITEM_H

#include <QtCore>
#include <QTreeWidgetItem>

#include "station/receiver.h"

class ReceiverTreeWidgetItem : public QTreeWidgetItem
{
public:
	ReceiverTreeWidgetItem(Receiver* receiver, QTreeWidgetItem* parent);
	~ReceiverTreeWidgetItem();

private:
	Receiver* receiver;
	QTreeWidgetItem* parent;
};

#endif // RECEIVERTREEWIDGETITEM_H
