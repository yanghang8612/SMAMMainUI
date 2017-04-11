#include "standardstationinfo_widget.h"
#include "ui_standardstationinfo_widget.h"

#include "common.h"

StandardStationInfoWidget::StandardStationInfoWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::StationInfoWidget)
{
	ui->setupUi(this);
    ui->receiverTable->horizontalHeader()->resizeSection(1, 100);
    ui->receiverTable->horizontalHeader()->resizeSection(2, 250);
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
    ui->receiverCountEdit->setText(QString::number(station->getReceivers().size()));
	ui->stationDetail->setText(station->getDetail());

	int index = 0;
	ui->receiverTable->setRowCount(station->getReceivers().size());
	foreach (Receiver* receiver, station->getReceivers()) {
		ui->receiverTable->setItem(index, 0, new QTableWidgetItem(receiver->getReceiverName()));
		ui->receiverTable->setItem(index, 1, new QTableWidgetItem("TCP/IP"));
		ui->receiverTable->setItem(index, 2, new QTableWidgetItem(
                                       QString::number(receiver->getLongitude()) + tr("° | ") +
                                       QString::number(receiver->getLatitude()) + tr("° | ") +
                                       QString::number(receiver->getHeight()) + "m"));
		ui->receiverTable->setItem(index, 3, new QTableWidgetItem(tr("离线")));
		index++;
	}
}
