#include "modify_center_dialog.h"
#include "ui_modify_center_dialog.h"

ModifyCenterDialog::ModifyCenterDialog(OtherCenter* center, QWidget *parent) :
	QDialog(parent),
    ui(new Ui::ModifyCenterDialog),
    center(center)
{
    ui->setupUi(this);
    ui->centerNameEdit->setText(center->getCenterName());
    ui->centerIPEdit->setText(center->getIpAddress());
    ui->centerPortEdit->setText(QString::number(center->getPort()));
    ui->centerDetailEdit->setText(center->getDetail());
    setWindowTitle(tr("编辑其他中心信息"));

    ui->centerNameEdit->setValidator(new QRegExpValidator(GeneralFunctions::nameRX, this));
    ui->centerIPEdit->setValidator(new QRegExpValidator(GeneralFunctions::ipAddressRX, this));
}

ModifyCenterDialog::~ModifyCenterDialog()
{
	delete ui;
}

void ModifyCenterDialog::on_confirmButton_clicked()
{
    center->setCenterName(ui->centerNameEdit->text());
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
