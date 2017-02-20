#include "igmasstationinfo_widget.h"
#include "ui_igmasstationinfo_widget.h"

IGMASStationInfoWidget::IGMASStationInfoWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::IGMASStationInfoWidget)
{
    ui->setupUi(this);
}

IGMASStationInfoWidget::~IGMASStationInfoWidget()
{
    delete ui;
}

void IGMASStationInfoWidget::setStation(IGMASStation* station)
{
    this->station = station;
    ui->stationMountEdit->setText(station->getMount());
    ui->stationIPEdit->setText(station->getIpAddress());
    ui->stationPortEdit->setText(QString::number(station->getPort()));
    ui->stationLongitudeEdit->setText(QString::number(station->getLongitude()));
    ui->stationLatitudeEdit->setText(QString::number(station->getLatitude()));
    ui->stationHeightEdit->setText(QString::number(station->getHeight()));
    ui->stationAvailableEdit->setText((station->getIsAvailable()) ? tr("可用") : tr("不可用"));
    ui->stationMemIDEdit->setText(QString::number(station->getMemID()));
}
