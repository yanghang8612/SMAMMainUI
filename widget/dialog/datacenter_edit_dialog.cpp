﻿#include "datacenter_edit_dialog.h"
#include "ui_datacenter_edit_dialog.h"

#include "utilities/general_functions.h"

DataCenterEditDialog::DataCenterEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataCenterEditDialog), dataCenter(new DataCenter())
{
    ui->setupUi(this);
    setWindowTitle(tr("添加数据中心"));
}

DataCenterEditDialog::DataCenterEditDialog(DataCenter* dataCenter, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::DataCenterEditDialog), dataCenter(dataCenter)
{
    ui->setupUi(this);
    ui->centerNameEdit->setText(dataCenter->getCenterName());
    ui->usernameEdit->setText(dataCenter->getUsername());
    ui->passwordEdit->setText(dataCenter->getPassword());
    ui->masterIPEdit->setText(dataCenter->getMasterIPAddress());
    ui->masterPortEdit->setText(QString::number(dataCenter->getMasterPort()));
    ui->slaveIPEdit->setText(dataCenter->getSlaveIPAddress());
    ui->slavePortEdit->setText(QString::number(dataCenter->getSlavePort()));
    ui->centerDetailEdit->setText(dataCenter->getCenterDetail());
    setWindowTitle(tr("编辑数据中心"));
}

DataCenterEditDialog::~DataCenterEditDialog()
{
    delete ui;
}

void DataCenterEditDialog::on_confirmButton_clicked()
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

    if (!GeneralFunctions::checkIPAddressString(ui->masterIPEdit->text())) {
        ui->masterIPEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->masterIPEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkPortString(ui->masterPortEdit->text())) {
        ui->masterPortEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->masterPortEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkIPAddressString(ui->slaveIPEdit->text())) {
        ui->slaveIPEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->slaveIPEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    if (!GeneralFunctions::checkPortString(ui->slavePortEdit->text())) {
        ui->slavePortEdit->setStyleSheet("QLineEdit{border-color:red}");
        return;
    }
    else {
        ui->slavePortEdit->setStyleSheet("QLineEdit{border-color:white}");
    }

    dataCenter->setCenterName(ui->centerNameEdit->text());
    dataCenter->setUsername(ui->usernameEdit->text());
    dataCenter->setPassword(ui->passwordEdit->text());
    dataCenter->setMasterIPAddress(ui->masterIPEdit->text());
    dataCenter->setMasterPort(ui->masterPortEdit->text());
    dataCenter->setSlaveIPAddress(ui->slaveIPEdit->text());
    dataCenter->setSlavePort(ui->slavePortEdit->text());
    dataCenter->setCenterDetail(ui->centerDetailEdit->toPlainText());

    emit confirmButtonClicked(dataCenter);
    QDialog::accept();
}

void DataCenterEditDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
