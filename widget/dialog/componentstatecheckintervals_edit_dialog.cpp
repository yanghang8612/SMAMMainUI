#include "componentstatecheckintervals_edit_dialog.h"
#include "ui_componentstatecheckintervals_edit_dialog.h"

#include "utilities/config_helper.h"

ComponentStateCheckIntervalsEditDialog::ComponentStateCheckIntervalsEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComponentStateCheckIntervalsEditDialog)
{
    ui->setupUi(this);
    ui->mainFrameWorkInterval->setValue(ConfigHelper::componentStateCheckIntervals[0]);
    ui->dataReceiveAndBroadcastInterval->setValue(ConfigHelper::componentStateCheckIntervals[1]);
    ui->dataProcessingInterval->setValue(ConfigHelper::componentStateCheckIntervals[2]);
    ui->dataStoringInterval->setValue(ConfigHelper::componentStateCheckIntervals[3]);
    ui->userManagerInterval->setValue(ConfigHelper::componentStateCheckIntervals[4]);
    ui->systemMonitorAndManagerInterval->setValue(ConfigHelper::componentStateCheckIntervals[5]);
    setWindowTitle(" ");
}

ComponentStateCheckIntervalsEditDialog::~ComponentStateCheckIntervalsEditDialog()
{
    delete ui;
}

void ComponentStateCheckIntervalsEditDialog::on_confirmButton_clicked()
{
    ConfigHelper::componentStateCheckIntervals.clear();
    ConfigHelper::componentStateCheckIntervals.append(ui->mainFrameWorkInterval->value());
    ConfigHelper::componentStateCheckIntervals.append(ui->dataReceiveAndBroadcastInterval->value());
    ConfigHelper::componentStateCheckIntervals.append(ui->dataProcessingInterval->value());
    ConfigHelper::componentStateCheckIntervals.append(ui->dataStoringInterval->value());
    ConfigHelper::componentStateCheckIntervals.append(ui->userManagerInterval->value());
    ConfigHelper::componentStateCheckIntervals.append(ui->systemMonitorAndManagerInterval->value());
    ConfigHelper::update();

    QDialog::accept();
}

void ComponentStateCheckIntervalsEditDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
