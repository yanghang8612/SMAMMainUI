#include "modify_user_dialog.h"
#include "ui_modify_user_dialog.h"

ModifyUserDialog::ModifyUserDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ModifyUserDialog)
{
	ui->setupUi(this);
}

ModifyUserDialog::~ModifyUserDialog()
{
	delete ui;
}
