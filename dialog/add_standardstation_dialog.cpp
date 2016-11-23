#include "add_standardstation_dialog.h"
#include "ui_add_standardstation_dialog.h"

AddStandardStationDialog::AddStandardStationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddStandardStationDialog)
{
	ui->setupUi(this);
	setWindowTitle(tr("添加基准站"));
}

AddStandardStationDialog::~AddStandardStationDialog()
{
	delete ui;
}

void AddStandardStationDialog::on_confirmButton_clicked()
{
	StandardStation* station = new StandardStation();
	station->setStationName(ui->stationNameEdit->text());
	station->setIpAddress(ui->stationIPEdit->text());
	station->setPort(ui->stationPortEdit->text());
	station->setMode(CasterMode::Value(ui->stationModeBox->currentIndex()));
	station->setServiceThreadCount(ui->stationThreadCountEdit->text());
	station->setDetail(ui->stationDetailEdit->toPlainText());

	emit confirmButtonClicked(station);

	QDialog::accept();
}

void AddStandardStationDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
