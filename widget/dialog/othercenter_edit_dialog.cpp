#include "othercenter_edit_dialog.h"
#include "ui_othercenter_edit_dialog.h"

#include "utilities/general_functions.h"

OtherCenterEditDialog::OtherCenterEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OtherCenterEditDialog), center(new OtherCenter())
{
    ui->setupUi(this);
    setWindowTitle(tr("添加数据中心"));
}

OtherCenterEditDialog::OtherCenterEditDialog(OtherCenter* center, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::OtherCenterEditDialog), center(center)
{
    ui->setupUi(this);
    ui->centerNameEdit->setText(center->getCenterName());
    ui->usernameEdit->setText(center->getUsername());
    ui->passwordEdit->setText(center->getPassword());
    ui->ipAddressEdit->setText(center->getIpAddress());
    ui->portEdit->setText(QString::number(center->getPort()));
    ui->detailEdit->setText(center->getDetail());
    setWindowTitle(tr("编辑数据中心信息"));
}

OtherCenterEditDialog::~OtherCenterEditDialog()
{
    delete ui;
}

void OtherCenterEditDialog::on_confirmButton_clicked()
{
    if (!GeneralFunctions::checkUserNameString(ui->usernameEdit->text())) {
        ui->usernameEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->usernameEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkPasswordString(ui->passwordEdit->text())) {
        ui->passwordEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->passwordEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkIPAddressString(ui->ipAddressEdit->text())) {
        ui->ipAddressEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->ipAddressEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkPortString(ui->portEdit->text())) {
        ui->portEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->portEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    center->setCenterName(ui->centerNameEdit->text());
    center->setUsername(ui->usernameEdit->text());
    center->setPassword(ui->passwordEdit->text());
    center->setIpAddress(ui->ipAddressEdit->text());
    center->setPort(ui->portEdit->text());
    center->setDetail(ui->detailEdit->toPlainText());

    emit confirmButtonClicked(center);
    QDialog::accept();
}

void OtherCenterEditDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
