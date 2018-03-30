#include "receiverinfo_widget.h"
#include "ui_receiverinfo_widget.h"

#include "utilities/general_functions.h"

ReceiverInfoWidget::ReceiverInfoWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::ReceiverInfoWidget)
{
	ui->setupUi(this);
    this->hide();
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
    ui->receiverMountEdit->setText(receiver->getMountPoint());
    ui->receiverLongitudeEdit->setText(GeneralFunctions::convertDMSToQString(receiver->getLongitude()));
    ui->receiverLatitudeEdit->setText(GeneralFunctions::convertDMSToQString(receiver->getLatitude()));
    ui->receiverHeightEdit->setText(QString::number(receiver->getHeight()));
    ui->receiverDetail->setText(receiver->getDetail());
}
