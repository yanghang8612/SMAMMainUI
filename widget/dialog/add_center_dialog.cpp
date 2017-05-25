#include "add_center_dialog.h"
#include "ui_add_center_dialog.h"

#include "utilies/general_functions.h"

AddCenterDialog::AddCenterDialog(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::AddCenterDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("添加数据中心"));
}

AddCenterDialog::~AddCenterDialog()
{
	delete ui;
}

void AddCenterDialog::on_confirmButton_clicked()
{
    if (!GeneralFunctions::checkIPAddressString(ui->centerIPEdit->text())) {
        ui->centerIPEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->centerIPEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkIPPortString(ui->centerPortEdit->text())) {
        ui->centerPortEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->centerPortEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkUserNameString(ui->centerUserNameEdit->text())) {
        ui->centerUserNameEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->centerUserNameEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkPasswordString(ui->centerPasswordEdit->text())) {
        ui->centerPasswordEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->centerPasswordEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    OtherCenter* center = new OtherCenter();
    center->setCenterName(ui->centerNameEdit->text());
    center->setUserName(ui->centerUserNameEdit->text());
    center->setPassword(ui->centerPasswordEdit->text());
    center->setIpAddress(ui->centerIPEdit->text());
    center->setPort(ui->centerPortEdit->text());
    center->setDetail(ui->centerDetailEdit->toPlainText());

    emit confirmButtonClicked(center);
	QDialog::accept();
}

void AddCenterDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
