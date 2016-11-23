#include "view_user_dialog.h"
#include "ui_view_user_dialog.h"

ViewUserDialog::ViewUserDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ViewUserDialog)
{
	ui->setupUi(this);
}

ViewUserDialog::~ViewUserDialog()
{
	delete ui;
}
