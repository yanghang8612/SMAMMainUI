#include "modify_standardstation_dialog.h"
#include "ui_modify_standardstation_dialog.h"

ModifyStandardStationDialog::ModifyStandardStationDialog(QWidget *parent, StandardStation* station) :
	QDialog(parent),
	ui(new Ui::ModifyStandardStationDialog),
	station(station)
{
	ui->setupUi(this);
	ui->stationNameEdit->setText(station->getStationName());
	ui->stationIPEdit->setText(station->getIpAddress());
	ui->stationPortEdit->setText(QString::number(station->getPort()));
	ui->stationModeBox->setCurrentIndex(station->getMode());
	ui->stationThreadCountEdit->setValue(station->getServiceThreadCount());
	ui->stationDetailEdit->setText(station->getDetail());
	setWindowTitle(tr("编辑基准站"));
}

ModifyStandardStationDialog::~ModifyStandardStationDialog()
{
	delete ui;
}

void ModifyStandardStationDialog::on_confirmButton_clicked()
{
	station->setStationName(ui->stationNameEdit->text());
	station->setIpAddress(ui->stationIPEdit->text());
	station->setPort(ui->stationPortEdit->text());
	station->setMode(CasterMode::Value(ui->stationModeBox->currentIndex()));
	station->setServiceThreadCount(ui->stationThreadCountEdit->text());
	station->setDetail(ui->stationDetailEdit->toPlainText());

	emit confirmButtonClicked(station);

	QDialog::accept();
}

void ModifyStandardStationDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
