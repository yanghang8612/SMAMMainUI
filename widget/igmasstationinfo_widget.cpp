#include "igmasstationinfo_widget.h"
#include "ui_igmasstationinfo_widget.h"

iGMASStationInfoWidget::iGMASStationInfoWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::iGMASStationInfoWidget)
{
    ui->setupUi(this);
}

iGMASStationInfoWidget::~iGMASStationInfoWidget()
{
    delete ui;
}

void iGMASStationInfoWidget::setStation(iGMASStation* station)
{
    this->station = station;
    ui->stationNameEdit->setText(station->getStationName());
    ui->mountPointEdit->setText(station->getMountPoint());
    ui->longitudeEdit->setText(QString::number(station->getLongitude()));
    ui->latitudeEdit->setText(QString::number(station->getLatitude()));
    ui->heightEdit->setText(QString::number(station->getHeight()));
    ui->detailEdit->setText(station->getDetail());
}
