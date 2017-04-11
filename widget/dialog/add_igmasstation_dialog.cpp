#include "add_igmasstation_dialog.h"
#include "ui_add_igmasstation_dialog.h"

#include "utilies/general_functions.h"

AddIGMASStationDialog::AddIGMASStationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIGMASStationDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("添加iGMAS测站"));
}

AddIGMASStationDialog::~AddIGMASStationDialog()
{
    delete ui;
}

void AddIGMASStationDialog::on_confirmButton_clicked()
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

    IGMASStation* station = new IGMASStation();
    station->setIsAvailable(ui->stationAvailableBox->currentIndex());
    station->setIpAddress(ui->stationIPEdit->text());
    station->setPort(ui->stationPortEdit->text());
    station->setMount(ui->stationMountEdit->text());
    station->setLongitude(ui->stationLongitudeEdit->text());
    station->setLatitude(ui->stationLatitudeEdit->text());
    station->setHeight(ui->stationHeightEdit->text());
    station->setUserName(ui->stationUserNameEdit->text());
    station->setPassword(ui->stationPasswordEdit->text());

    emit confirmButtonClicked(station);
    QDialog::accept();
}

void AddIGMASStationDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
