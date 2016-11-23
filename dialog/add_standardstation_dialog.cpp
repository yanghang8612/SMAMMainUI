#include "add_standardstation_dialog.h"
#include "ui_add_standardstation_dialog.h"

AddStandardStationDialog::AddStandardStationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddStandardStationDialog)
{
	ui->setupUi(this);
}

AddStandardStationDialog::~AddStandardStationDialog()
{
	delete ui;
}
