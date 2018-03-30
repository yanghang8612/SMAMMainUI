#include "monitorstation_edit_dialog.h"
#include "ui_monitorstation_edit_dialog.h"

#include "utilities/general_functions.h"

MonitorStationEditDialog::MonitorStationEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorStationEditDialog), station(new MonitorStation())
{
    ui->setupUi(this);
    setWindowTitle(tr("添加监测站"));
}

MonitorStationEditDialog::MonitorStationEditDialog(MonitorStation* station, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::MonitorStationEditDialog), station(station)
{
    ui->setupUi(this);
    ui->stationNameEdit->setText(station->getStationName());
    ui->mountPointEdit->setText(station->getMountPoint());
    ui->longitudeDegree->setValue(station->getLongitude().degree);
    ui->longitudeMinute->setValue(station->getLongitude().minute);
    ui->longitudeSecond->setValue(station->getLongitude().second);
    ui->longitudeFractionalPart->setValue(station->getLongitude().fractionalPart);
    ui->latitudeDegree->setValue(station->getLatitude().degree);
    ui->latitudeMinute->setValue(station->getLatitude().minute);
    ui->latitudeSecond->setValue(station->getLatitude().second);
    ui->latitudeFractionalPart->setValue(station->getLatitude().fractionalPart);
    ui->height->setValue(station->getHeight());
    ui->detailEdit->setText(station->getDetail());
    setWindowTitle(tr("编辑监测站"));
}

MonitorStationEditDialog::~MonitorStationEditDialog()
{
    delete ui;
}

void MonitorStationEditDialog::on_confirmButton_clicked()
{
    if (!GeneralFunctions::checkMountPointString(ui->mountPointEdit->text())) {
        ui->mountPointEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->mountPointEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    station->setStationName(ui->stationNameEdit->text());
    station->setMountPoint(ui->mountPointEdit->text());
    DMS longitude;
    longitude.degree = ui->longitudeDegree->value();
    longitude.minute = ui->longitudeMinute->value();
    longitude.second = ui->longitudeSecond->value();
    longitude.fractionalPart = ui->longitudeFractionalPart->value();
    station->setLongitude(longitude);
    DMS latitude;
    latitude.degree = ui->latitudeDegree->value();
    latitude.minute = ui->latitudeMinute->value();
    latitude.second = ui->latitudeSecond->value();
    latitude.fractionalPart = ui->latitudeFractionalPart->value();
    station->setLatitude(latitude);
    station->setHeight(ui->height->value());
    station->setDetail(ui->detailEdit->toPlainText());

    emit confirmButtonClicked(station);
    QDialog::accept();
}

void MonitorStationEditDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
