#include <QDateTime>
#include <QMessageBox>

#include "add_center_dialog.h"
#include "ui_add_center_dialog.h"

AddCenterDialog::AddCenterDialog(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::AddCenterDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("添加其他中心"));
}

AddCenterDialog::~AddCenterDialog()
{
	delete ui;
}

void AddCenterDialog::on_confirmButton_clicked()
{
    OtherCenter* center = new OtherCenter();
    center->setCenterName(ui->centerNameEdit->text());
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
