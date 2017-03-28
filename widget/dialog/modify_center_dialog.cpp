#include "modify_center_dialog.h"
#include "ui_modify_center_dialog.h"
#include "utilies/general_functions.h"

ModifyCenterDialog::ModifyCenterDialog(OtherCenter* center, QWidget *parent) :
	QDialog(parent),
    ui(new Ui::ModifyCenterDialog), center(center)
{
    ui->setupUi(this);
    ui->centerNameEdit->setText(center->getCenterName());
    ui->centerUserNameEdit->setText(center->getUserName());
    ui->centerPasswordEdit->setText(center->getPassword());
    ui->centerIPEdit->setText(center->getIpAddress());
    ui->centerPortEdit->setText(QString::number(center->getPort()));
    ui->centerDetailEdit->setText(center->getDetail());
    setWindowTitle(tr("编辑其他中心信息"));

    ui->centerIPEdit->setValidator(new QRegExpValidator(GeneralFunctions::ipAddressRX, this));
}

ModifyCenterDialog::~ModifyCenterDialog()
{
	delete ui;
}

void ModifyCenterDialog::on_confirmButton_clicked()
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

    center->setCenterName(ui->centerNameEdit->text());
    center->setUserName(ui->centerUserNameEdit->text());
    center->setPassword(ui->centerPasswordEdit->text());
    center->setIpAddress(ui->centerIPEdit->text());
    center->setPort(ui->centerPortEdit->text());
    center->setDetail(ui->centerDetailEdit->toPlainText());

    emit confirmButtonClicked(center);
	QDialog::accept();
}

void ModifyCenterDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
