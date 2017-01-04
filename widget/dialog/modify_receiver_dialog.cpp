#include "modify_receiver_dialog.h"
#include "ui_modify_receiver_dialog.h"
#include "utilies/general_functions.h"

ModifyReceiverDialog::ModifyReceiverDialog(Receiver* receiver, QWidget *parent) :
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

    ui->receiverNameEdit->setValidator(new QRegExpValidator(GeneralFunctions::nameRX, this));
    ui->receiverIPEdit->setValidator(new QRegExpValidator(GeneralFunctions::ipAddressRX, this));
    ui->receiverLongitudeEdit->setValidator(new QRegExpValidator(GeneralFunctions::longitudeRX, this));
    ui->receiverLatitudeEdit->setValidator(new QRegExpValidator(GeneralFunctions::latitudeRX, this));
}

ModifyReceiverDialog::~ModifyReceiverDialog()
{
	delete ui;
}

void ModifyReceiverDialog::on_confirmButton_clicked()
{
    if (!GeneralFunctions::checkNameString(ui->receiverNameEdit->text())) {
        ui->receiverNameEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->receiverNameEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

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
