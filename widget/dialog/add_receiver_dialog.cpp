#include "add_receiver_dialog.h"
#include "ui_add_receiver_dialog.h"
#include "utilies/general_functions.h"

AddReceiverDialog::AddReceiverDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddReceiverDialog)
{
	ui->setupUi(this);
	setWindowTitle(tr("添加接收机"));

    ui->receiverNameEdit->setValidator(new QRegExpValidator(GeneralFunctions::nameRX, this));
    ui->receiverIPEdit->setValidator(new QRegExpValidator(GeneralFunctions::ipAddressRX, this));
    ui->receiverLongitudeEdit->setValidator(new QRegExpValidator(GeneralFunctions::longitudeRX, this));
    ui->receiverLatitudeEdit->setValidator(new QRegExpValidator(GeneralFunctions::latitudeRX, this));
    ui->receiverHeightEdit->setValidator(new QRegExpValidator(GeneralFunctions::heightRX, this));
}

AddReceiverDialog::~AddReceiverDialog()
{
	delete ui;
}

void AddReceiverDialog::on_confirmButton_clicked()
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

    if (!GeneralFunctions::checkHeightString(ui->receiverHeightEdit->text())) {
        ui->receiverHeightEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->receiverHeightEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

	Receiver* receiver = new Receiver();
	receiver->setReceiverName(ui->receiverNameEdit->text());
	receiver->setIpAddress(ui->receiverIPEdit->text());
	receiver->setPort(ui->receiverPortEdit->text());
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
