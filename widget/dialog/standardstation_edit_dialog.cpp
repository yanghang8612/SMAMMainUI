#include "standardstation_edit_dialog.h"
#include "ui_standardstation_edit_dialog.h"

#include "utilities/general_functions.h"

StandardStationEditDialog::StandardStationEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StandardStationEditDialog), station(new StandardStation())
{
    ui->setupUi(this);
    setWindowTitle(tr("添加基准站"));
}

StandardStationEditDialog::StandardStationEditDialog(StandardStation* station, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::StandardStationEditDialog), station(station)
{
    ui->setupUi(this);
    ui->stationNameEdit->setText(station->getStationName());
    ui->detailEdit->setText(station->getDetail());
    setWindowTitle(tr("编辑基准站"));
}

StandardStationEditDialog::~StandardStationEditDialog()
{
    delete ui;
}

void StandardStationEditDialog::on_confirmButton_clicked()
{
    station->setStationName(ui->stationNameEdit->text());
    station->setDetail(ui->detailEdit->toPlainText());

    emit confirmButtonClicked(station);
    QDialog::accept();
}

void StandardStationEditDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
