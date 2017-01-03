#include "modify_user_dialog.h"
#include "ui_modify_user_dialog.h"

ModifyUserDialog::ModifyUserDialog(QWidget *parent, BaseUser* user) :
	QDialog(parent),
	ui(new Ui::ModifyUserDialog),
	user(user)
{
	ui->setupUi(this);
	ui->userNameEdit->setText(user->getUserName());
	ui->userPasswordEdit->setText(user->getUserPassword());
	ui->confirmUserPasswordEdit->setText(user->getUserPassword());
	ui->userLevelBox->setCurrentIndex((int) user->getUserLevel() - 65);
	ui->terminalTypeBox->setValue(user->getTerminalType());
	ui->terminalIDEdit->setText(user->getTerminalID());
	ui->serviceDeadlineEdit->setDateTime(user->getServiceDeadline());
	setWindowTitle(tr("编辑用户信息"));
}

ModifyUserDialog::~ModifyUserDialog()
{
	delete ui;
}

void ModifyUserDialog::on_confirmButton_clicked()
{
	user->setUserName(ui->userNameEdit->text());
	user->setUserPassword(ui->userPasswordEdit->text());
	user->setUserLevel(ui->userLevelBox->currentText());
	user->setServiceDeadline(ui->serviceDeadlineEdit->dateTime());
	user->setTerminalType(ui->terminalTypeBox->value());
	user->setTerminalID(ui->terminalIDEdit->text());
	emit confirmButtonClicked(user);

	QDialog::accept();
}

void ModifyUserDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
