#include "standardstationinfo_widget.h"
#include "ui_standardstationinfo_widget.h"
#include "common.h"

StandardStationInfoWidget::StandardStationInfoWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::StationInfoWidget)
{
	ui->setupUi(this);
	ui->receiverTable->horizontalHeader()->resizeSection(1, 150);
	ui->receiverTable->horizontalHeader()->resizeSection(2, 150);
	ui->receiverTable->horizontalHeader()->setFixedHeight(TABLEWIDGET_HORIZONHEADER_HEIGHT);
	ui->receiverTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->receiverTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->receiverTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->receiverTable->verticalHeader()->setVisible(false);
}

StandardStationInfoWidget::~StandardStationInfoWidget()
{
	delete ui;
}

void StandardStationInfoWidget::setStation(StandardStation* station)
{
	this->station = station;
	ui->stationNameEdit->setText(station->getStationName());
	ui->stationIPEdit->setText(station->getIpAddress());
	ui->stationPortEdit->setText(QString::number(station->getPort()));
	if (station->getMode() == CasterMode::IMMEDIATE_CASTER) {
		ui->stationModeEdit->setText(tr("IMMEDIATE_CASTER"));
	}
	else if (station->getMode() == CasterMode::PROCESS_CASTER) {
		ui->stationModeEdit->setText(tr("PROCESS_CASTER"));
	}
	ui->stationThreadCountEdit->setText(QString::number(station->getServiceThreadCount()));
	ui->stationDetail->setText(station->getDetail());

	int index = 0;
	ui->receiverTable->setRowCount(station->getReceivers().size());
	foreach (Receiver* receiver, station->getReceivers()) {
		ui->receiverTable->setItem(index, 0, new QTableWidgetItem(receiver->getReceiverName()));
		ui->receiverTable->setItem(index, 1, new QTableWidgetItem("TCP/IP"));
		ui->receiverTable->setItem(index, 2, new QTableWidgetItem(
									   QString::number(receiver->getLongitude()) + " | " + QString::number(receiver->getLatitude())));
		ui->receiverTable->setItem(index, 3, new QTableWidgetItem(tr("离线")));
		index++;
	}
}
