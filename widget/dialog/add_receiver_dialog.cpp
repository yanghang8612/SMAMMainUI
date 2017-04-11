#include "add_receiver_dialog.h"
#include "ui_add_receiver_dialog.h"

#include "utilies/general_functions.h"

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
    if (!GeneralFunctions::checkIPAddressString(ui->receiverIPEdit->text())) {
        ui->receiverIPEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->receiverIPEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkIPPortString(ui->receiverPortEdit->text())) {
        ui->receiverPortEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->receiverPortEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkLongitudeString(ui->receiverLongitudeEdit->text())) {
        ui->receiverLongitudeEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->receiverLongitudeEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkLatitudeString(ui->receiverLatitudeEdit->text())) {
        ui->receiverLatitudeEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->receiverLatitudeEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkHeightString(ui->receiverHeightEdit->text())) {
        ui->receiverHeightEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->receiverHeightEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

	Receiver* receiver = new Receiver();
	receiver->setReceiverName(ui->receiverNameEdit->text());
    receiver->setPassword(ui->receiverPasswordEdit->text());
	receiver->setIpAddress(ui->receiverIPEdit->text());
	receiver->setPort(ui->receiverPortEdit->text());
    receiver->setMount(ui->receiverMountEdit->text());
	receiver->setLongitude(ui->receiverLongitudeEdit->text());
	receiver->setLatitude(ui->receiverLatitudeEdit->text());
    receiver->setHeight(ui->receiverHeightEdit->text());
    receiver->setDetail(ui->receiverDetailEdit->toPlainText());

	emit confirmButtonClicked(receiver);

	QDialog::accept();
}

void AddReceiverDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
