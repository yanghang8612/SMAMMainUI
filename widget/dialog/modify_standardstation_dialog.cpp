#include "modify_standardstation_dialog.h"
#include "ui_modify_standardstation_dialog.h"
#include "utilies/general_functions.h"

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
    ui->stationNameEdit->setValidator(new QRegExpValidator(GeneralFunctions::nameRX, this));
    ui->stationIPEdit->setValidator(new QRegExpValidator(GeneralFunctions::ipAddressRX, this));
}

ModifyStandardStationDialog::~ModifyStandardStationDialog()
{
	delete ui;
}

void ModifyStandardStationDialog::on_confirmButton_clicked()
{
    if (!GeneralFunctions::checkNameString(ui->stationNameEdit->text())) {
        ui->stationNameEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->stationNameEdit->setStyleSheet("QLineEdit{border-color:white}");
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
