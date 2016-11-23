#include "modify_receiver_dialog.h"
#include "ui_modify_receiver_dialog.h"

ModifyReceiverDialog::ModifyReceiverDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ModifyReceiverDialog)
{
	ui->setupUi(this);
}

ModifyReceiverDialog::~ModifyReceiverDialog()
{
	delete ui;
}
