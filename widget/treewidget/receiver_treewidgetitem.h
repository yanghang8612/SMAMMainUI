#ifndef RECEIVERTREEWIDGETITEM_H
#define RECEIVERTREEWIDGETITEM_H

#include <QtCore>
#include <QTreeWidgetItem>

#include "station/receiver.h"

class ReceiverTreeWidgetItem : public QTreeWidgetItem
{
public:
	ReceiverTreeWidgetItem(QTreeWidgetItem* parent = 0, Receiver* receiver = 0);
	~ReceiverTreeWidgetItem();

private:
	Receiver* receiver;
	QTreeWidgetItem* parent;
};

#endif // RECEIVERTREEWIDGETITEM_H
