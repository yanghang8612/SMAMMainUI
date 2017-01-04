#include "add_standardstation_dialog.h"
#include "ui_add_standardstation_dialog.h"
#include "utilies/general_functions.h"

AddStandardStationDialog::AddStandardStationDialog(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::AddStandardStationDialog)
{
	ui->setupUi(this);
    setWindowTitle(tr("添加基准站"));
    ui->stationNameEdit->setValidator(new QRegExpValidator(GeneralFunctions::nameRX, this));
    ui->stationIPEdit->setValidator(new QRegExpValidator(GeneralFunctions::ipAddressRX, this));
}

AddStandardStationDialog::~AddStandardStationDialog()
{
	delete ui;
}

void AddStandardStationDialog::on_confirmButton_clicked()
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
