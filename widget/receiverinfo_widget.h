#ifndef RECEIVERINFO_WIDGET_H
#define RECEIVERINFO_WIDGET_H

#include <QTabWidget>

namespace Ui {
	class ReceiverInfoWidget;
}

class ReceiverInfoWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit ReceiverInfoWidget(QWidget *parent = 0);
	~ReceiverInfoWidget();

private:
	Ui::ReceiverInfoWidget *ui;
};

#endif // RECEIVERINFO_WIDGET_H
