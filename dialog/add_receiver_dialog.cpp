#include "add_receiver_dialog.h"
#include "ui_add_receiver_dialog.h"

AddReceiverDialog::AddReceiverDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddReceiverDialog)
{
	ui->setupUi(this);
}

AddReceiverDialog::~AddReceiverDialog()
{
	delete ui;
}
