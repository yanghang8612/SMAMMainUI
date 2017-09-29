#include "receiver_edit_dialog.h"
#include "ui_receiver_edit_dialog.h"

#include "utilities/general_functions.h"

ReceiverEditDialog::ReceiverEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiverEditDialog), receiver(new Receiver())
{
    ui->setupUi(this);
    setWindowTitle(tr("添加接收机"));
}

ReceiverEditDialog::ReceiverEditDialog(Receiver* receiver, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ReceiverEditDialog), receiver(receiver)
{
    ui->setupUi(this);
    ui->receiverNameEdit->setText(receiver->getReceiverName());
    ui->passwordEdit->setText(receiver->getPassword());
    ui->ipAddressEdit->setText(receiver->getIpAddress());
    ui->portEdit->setText(QString::number(receiver->getPort()));
    ui->mountPointEdit->setText(receiver->getMountPoint());
    ui->longitudeEdit->setText(QString::number(receiver->getLongitude()));
    ui->latitudeEdit->setText(QString::number(receiver->getLatitude()));
    ui->heightEdit->setText(QString::number(receiver->getHeight()));
    ui->detailEdit->setText(receiver->getDetail());
    setWindowTitle(tr("编辑接收机"));
}

ReceiverEditDialog::~ReceiverEditDialog()
{
    delete ui;
}

void ReceiverEditDialog::on_confirmButton_clicked()
{
    if (!GeneralFunctions::checkIPAddressString(ui->ipAddressEdit->text())) {
        ui->ipAddressEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->ipAddressEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkPortString(ui->portEdit->text())) {
        ui->portEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->portEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkLongitudeString(ui->longitudeEdit->text())) {
        ui->longitudeEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->longitudeEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkLatitudeString(ui->latitudeEdit->text())) {
        ui->latitudeEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->latitudeEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkHeightString(ui->heightEdit->text())) {
        ui->heightEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->heightEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    receiver->setReceiverName(ui->receiverNameEdit->text());
    receiver->setPassword(ui->passwordEdit->text());
    receiver->setIpAddress(ui->ipAddressEdit->text());
    receiver->setPort(ui->portEdit->text());
    receiver->setMountPoint(ui->mountPointEdit->text());
    receiver->setLongitude(ui->longitudeEdit->text());
    receiver->setLatitude(ui->latitudeEdit->text());
    receiver->setHeight(ui->heightEdit->text());
    receiver->setDetail(ui->detailEdit->toPlainText());

    emit confirmButtonClicked(receiver);
    QDialog::accept();
}

void ReceiverEditDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
