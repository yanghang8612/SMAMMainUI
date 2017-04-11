#include "modify_igmasstation_dialog.h"
#include "ui_modify_igmasstation_dialog.h"

#include "utilies/general_functions.h"

ModifyIGMASStationDialog::ModifyIGMASStationDialog(IGMASStation* station, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ModifyIGMASStationDialog), station(station)
{
    ui->setupUi(this);
    ui->stationMountEdit->setText(station->getMount());
    ui->stationIPEdit->setText(station->getIpAddress());
    ui->stationPortEdit->setText(QString::number(station->getPort()));
    ui->stationLongitudeEdit->setText(QString::number(station->getLongitude()));
    ui->stationLatitudeEdit->setText(QString::number(station->getLatitude()));
    ui->stationHeightEdit->setText(QString::number(station->getHeight()));
    ui->stationAvailableBox->setCurrentIndex((station->getIsAvailable()) ? 1 : 0);
    ui->stationUserNameEdit->setText(station->getUserName());
    ui->stationPasswordEdit->setText(station->getPassword());
    setWindowTitle(tr("编辑iGMAS测站"));
}

ModifyIGMASStationDialog::~ModifyIGMASStationDialog()
{
    delete ui;
}

void ModifyIGMASStationDialog::on_confirmButton_clicked()
{
    if (!GeneralFunctions::checkMountString(ui->stationMountEdit->text())) {
        ui->stationMountEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationMountEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkIPAddressString(ui->stationIPEdit->text())) {
        ui->stationIPEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationIPEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkIPPortString(ui->stationPortEdit->text())) {
        ui->stationPortEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationPortEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkLongitudeString(ui->stationLongitudeEdit->text())) {
        ui->stationLongitudeEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationLongitudeEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkLatitudeString(ui->stationLatitudeEdit->text())) {
        ui->stationLatitudeEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationLatitudeEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkHeightString(ui->stationHeightEdit->text())) {
        ui->stationHeightEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationHeightEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkUserNameString(ui->stationUserNameEdit->text())) {
        ui->stationUserNameEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationUserNameEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkPasswordString(ui->stationPasswordEdit->text())) {
        ui->stationPasswordEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationPasswordEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    station->setIpAddress(ui->stationIPEdit->text());
    station->setPort(ui->stationPortEdit->text());
    station->setIsAvailable(ui->stationAvailableBox->currentIndex());
    station->setMount(ui->stationMountEdit->text());
    station->setLongitude(ui->stationLongitudeEdit->text());
    station->setLatitude(ui->stationLatitudeEdit->text());
    station->setHeight(ui->stationHeightEdit->text());
    station->setUserName(ui->stationUserNameEdit->text());
    station->setPassword(ui->stationPasswordEdit->text());

    emit confirmButtonClicked(station);
    QDialog::accept();
}

void ModifyIGMASStationDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
