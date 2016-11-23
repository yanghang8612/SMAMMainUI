#ifndef RECEIVERINFO_WIDGET_H
#define RECEIVERINFO_WIDGET_H

#include <QTabWidget>
#include <QtGui>

#include "station/receiver.h"

namespace Ui {
	class ReceiverInfoWidget;
}

class ReceiverInfoWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit ReceiverInfoWidget(QWidget *parent = 0);
	~ReceiverInfoWidget();
	void setReceiver(Receiver* receiver);

private:
	Ui::ReceiverInfoWidget *ui;
	Receiver* receiver;
};

#endif // RECEIVERINFO_WIDGET_H
