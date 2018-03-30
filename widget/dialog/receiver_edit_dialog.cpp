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
    ui->longitudeDegree->setValue(receiver->getLongitude().degree);
    ui->longitudeMinute->setValue(receiver->getLongitude().minute);
    ui->longitudeSecond->setValue(receiver->getLongitude().second);
    ui->longitudeFractionalPart->setValue(receiver->getLongitude().fractionalPart);
    ui->latitudeDegree->setValue(receiver->getLatitude().degree);
    ui->latitudeMinute->setValue(receiver->getLatitude().minute);
    ui->latitudeSecond->setValue(receiver->getLatitude().second);
    ui->latitudeFractionalPart->setValue(receiver->getLatitude().fractionalPart);
    ui->height->setValue(receiver->getHeight());
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

    receiver->setReceiverName(ui->receiverNameEdit->text());
    receiver->setPassword(ui->passwordEdit->text());
    receiver->setIpAddress(ui->ipAddressEdit->text());
    receiver->setPort(ui->portEdit->text());
    receiver->setMountPoint(ui->mountPointEdit->text());
    DMS longitude;
    longitude.degree = ui->longitudeDegree->value();
    longitude.minute = ui->longitudeMinute->value();
    longitude.second = ui->longitudeSecond->value();
    longitude.fractionalPart = ui->longitudeFractionalPart->value();
    receiver->setLongitude(longitude);
    DMS latitude;
    latitude.degree = ui->latitudeDegree->value();
    latitude.minute = ui->latitudeMinute->value();
    latitude.second = ui->latitudeSecond->value();
    latitude.fractionalPart = ui->latitudeFractionalPart->value();
    receiver->setLatitude(latitude);
    receiver->setHeight(ui->height->value());
    receiver->setDetail(ui->detailEdit->toPlainText());

    emit confirmButtonClicked(receiver);
    QDialog::accept();
}

void ReceiverEditDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
