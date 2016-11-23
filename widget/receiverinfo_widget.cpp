#include "receiverinfo_widget.h"
#include "ui_receiverinfo_widget.h"

ReceiverInfoWidget::ReceiverInfoWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::ReceiverInfoWidget)
{
	ui->setupUi(this);
}

ReceiverInfoWidget::~ReceiverInfoWidget()
{
	delete ui;
}
