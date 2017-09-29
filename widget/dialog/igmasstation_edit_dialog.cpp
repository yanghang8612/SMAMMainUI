#include "igmasstation_edit_dialog.h"
#include "ui_igmasstation_edit_dialog.h"

#include "utilities/general_functions.h"

iGMASStationEditDialog::iGMASStationEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::iGMASStationEditDialog), station(new iGMASStation())
{
    ui->setupUi(this);
    setWindowTitle(tr("添加iGMAS测站"));
}

iGMASStationEditDialog::iGMASStationEditDialog(iGMASStation* station, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::iGMASStationEditDialog), station(station)
{
    ui->setupUi(this);
    ui->stationNameEdit->setText(station->getStationName());
    ui->mountPointEdit->setText(station->getMountPoint());
    ui->longitudeEdit->setText(QString::number(station->getLongitude()));
    ui->latitudeEdit->setText(QString::number(station->getLatitude()));
    ui->heightEdit->setText(QString::number(station->getHeight()));
    ui->detailEdit->setText(station->getDetail());
    setWindowTitle(tr("编辑iGMAS测站"));
}

iGMASStationEditDialog::~iGMASStationEditDialog()
{
    delete ui;
}

void iGMASStationEditDialog::on_confirmButton_clicked()
{
    if (!GeneralFunctions::checkMountPointString(ui->mountPointEdit->text())) {
        ui->mountPointEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->mountPointEdit->setStyleSheet("QLineEdit{border-color:white}");
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

    station->setStationName(ui->stationNameEdit->text());
    station->setMountPoint(ui->mountPointEdit->text());
    station->setLongitude(ui->longitudeEdit->text());
    station->setLatitude(ui->latitudeEdit->text());
    station->setHeight(ui->heightEdit->text());
    station->setDetail(ui->detailEdit->toPlainText());

    emit confirmButtonClicked(station);
    QDialog::accept();
}

void iGMASStationEditDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
