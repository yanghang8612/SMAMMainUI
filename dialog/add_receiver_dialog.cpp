#include "add_receiver_dialog.h"
#include "ui_add_receiver_dialog.h"

AddReceiverDialog::AddReceiverDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddReceiverDialog)
{
	ui->setupUi(this);
	setWindowTitle(tr("添加接收机"));
}

AddReceiverDialog::~AddReceiverDialog()
{
	delete ui;
}

void AddReceiverDialog::on_confirmButton_clicked()
{
	Receiver* receiver = new Receiver();
	receiver->setReceiverName(ui->receiverNameEdit->text());
	receiver->setIpAddress(ui->receiverIPEdit->text());
	receiver->setPort(ui->receiverPortEdit->text());
	receiver->setLongitude(ui->receiverLongitudeEdit->text());
	receiver->setLatitude(ui->receiverLatitudeEdit->text());

	emit confirmButtonClicked(receiver);

	QDialog::accept();
}

void AddReceiverDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
