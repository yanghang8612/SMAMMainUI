#include "modify_receiver_dialog.h"
#include "ui_modify_receiver_dialog.h"

ModifyReceiverDialog::ModifyReceiverDialog(QWidget *parent, Receiver* receiver) :
	QDialog(parent),
	ui(new Ui::ModifyReceiverDialog),
	receiver(receiver)
{
	ui->setupUi(this);
	ui->receiverNameEdit->setText(receiver->getReceiverName());
	ui->receiverIPEdit->setText(receiver->getIpAddress());
	ui->receiverPortEdit->setText(QString::number(receiver->getPort()));
	ui->receiverLongitudeEdit->setText(QString::number(receiver->getLongitude()));
	ui->receiverLatitudeEdit->setText(QString::number(receiver->getLatitude()));
	setWindowTitle(tr("编辑接收机"));
}

ModifyReceiverDialog::~ModifyReceiverDialog()
{
	delete ui;
}

void ModifyReceiverDialog::on_confirmButton_clicked()
{
	receiver->setReceiverName(ui->receiverNameEdit->text());
	receiver->setIpAddress(ui->receiverIPEdit->text());
	receiver->setPort(ui->receiverPortEdit->text());
	receiver->setLongitude(ui->receiverLongitudeEdit->text());
	receiver->setLatitude(ui->receiverLatitudeEdit->text());

	emit confirmButtonClicked(receiver);

	QDialog::accept();
}

void ModifyReceiverDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
