#include "modify_standardstation_dialog.h"
#include "ui_modify_standardstation_dialog.h"

#include "utilies/general_functions.h"

ModifyStandardStationDialog::ModifyStandardStationDialog(StandardStation* station, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ModifyStandardStationDialog),
	station(station)
{
	ui->setupUi(this);
    ui->stationNameEdit->setText(station->getStationName());
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
	station->setDetail(ui->stationDetailEdit->toPlainText());

	emit confirmButtonClicked(station);

	QDialog::accept();
}

void ModifyStandardStationDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
