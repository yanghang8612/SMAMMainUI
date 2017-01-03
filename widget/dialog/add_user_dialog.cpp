#include <QDateTime>
#include <QMessageBox>

#include "add_user_dialog.h"
#include "ui_add_user_dialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddUserDialog)
{
	ui->setupUi(this);
	ui->serviceDeadlineEdit->setDateTime(QDateTime::currentDateTime());
	setWindowTitle(tr("添加用户"));
}

AddUserDialog::~AddUserDialog()
{
	delete ui;
}

void AddUserDialog::on_confirmButton_clicked()
{
	if (ui->userPasswordEdit->text() != ui->confirmUserPasswordEdit->text()) {
		QMessageBox::critical(this, tr("提示"), tr("两次输入密码不一致"));
		return;
	}

	BaseUser* user = new BaseUser();
	user->setUserName(ui->userNameEdit->text());
	user->setUserPassword(ui->userPasswordEdit->text());
	user->setUserLevel(ui->userLevelBox->currentText());
	user->setServiceDeadline(ui->serviceDeadlineEdit->dateTime());
	user->setTerminalType(ui->terminalTypeBox->value());
	user->setTerminalID(ui->terminalIDEdit->text());
	emit confirmButtonClicked(user);

	QDialog::accept();
}

void AddUserDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
