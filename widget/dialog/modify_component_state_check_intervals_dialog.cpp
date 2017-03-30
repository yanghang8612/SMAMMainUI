#include "modify_component_state_check_intervals_dialog.h"
#include "ui_modify_component_state_check_intervals_dialog.h"

ModifyComponentStateCheckIntervalsDialog::ModifyComponentStateCheckIntervalsDialog(QList<int> componentStateCheckIntervals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyComponentStateCheckIntervalsDialog), componentStateCheckIntervals(componentStateCheckIntervals)
{
    ui->setupUi(this);
    ui->mainFrameWorkInterval->setValue(componentStateCheckIntervals[0]);
    ui->dataReceiveAndBroadcastInterval->setValue(componentStateCheckIntervals[1]);
    ui->dataProcessingInterval->setValue(componentStateCheckIntervals[2]);
    ui->dataStoringInterval->setValue(componentStateCheckIntervals[3]);
    ui->userManagerInterval->setValue(componentStateCheckIntervals[4]);
    ui->systemMonitorAndManagerInterval->setValue(componentStateCheckIntervals[5]);
    setWindowTitle(" ");
}

ModifyComponentStateCheckIntervalsDialog::~ModifyComponentStateCheckIntervalsDialog()
{
    delete ui;
}

void ModifyComponentStateCheckIntervalsDialog::on_confirmButton_clicked()
{
    componentStateCheckIntervals.clear();
    componentStateCheckIntervals.append(ui->mainFrameWorkInterval->value());
    componentStateCheckIntervals.append(ui->dataReceiveAndBroadcastInterval->value());
    componentStateCheckIntervals.append(ui->dataProcessingInterval->value());
    componentStateCheckIntervals.append(ui->dataStoringInterval->value());
    componentStateCheckIntervals.append(ui->userManagerInterval->value());
    componentStateCheckIntervals.append(ui->systemMonitorAndManagerInterval->value());

    emit confirmButtonClicked(componentStateCheckIntervals);
    QDialog::accept();
}

void ModifyComponentStateCheckIntervalsDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
