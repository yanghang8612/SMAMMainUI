#include "modify_standardstation_dialog.h"
#include "ui_modify_standardstation_dialog.h"

ModifyStandardStationDialog::ModifyStandardStationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ModifyStandardStationDialog)
{
	ui->setupUi(this);
}

ModifyStandardStationDialog::~ModifyStandardStationDialog()
{
	delete ui;
}
