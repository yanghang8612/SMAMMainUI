#include "receiverinfo_widget.h"
#include "ui_receiverinfo_widget.h"

ReceiverInfoWidget::ReceiverInfoWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::ReceiverInfoWidget)
{
	ui->setupUi(this);
	int l = ui->satelliteDistributionContainer->size().width();
	ui->satelliteDistributionContainer->setPixmap(QPixmap(":/satellite_distribution").scaled(l, l, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

ReceiverInfoWidget::~ReceiverInfoWidget()
{
	delete ui;
}

void ReceiverInfoWidget::setReceiver(Receiver* receiver)
{
	this->receiver = receiver;
	ui->receiverNameEdit->setText(receiver->getReceiverName());
	ui->receiverIPEdit->setText(receiver->getIpAddress());
	ui->receiverPortEdit->setText(QString::number(receiver->getPort()));
	ui->receiverLongitudeEdit->setText(QString::number(receiver->getLongitude()));
	ui->receiverLatitudeEdit->setText(QString::number(receiver->getLatitude()));
    ui->receiverHeightEdit->setText(QString::number(receiver->getHeight()));
    ui->receiverDetail->setText(receiver->getDetail());
}
