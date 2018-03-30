#ifndef MONITORSTATION_EDIT_DIALOG_H
#define MONITORSTATION_EDIT_DIALOG_H

#include <QDialog>

#include "bean/monitor_station.h"

namespace Ui {
class MonitorStationEditDialog;
}

class MonitorStationEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonitorStationEditDialog(QWidget *parent = 0);
    explicit MonitorStationEditDialog(MonitorStation* station, QWidget *parent = 0);
    ~MonitorStationEditDialog();

signals:
    void confirmButtonClicked(MonitorStation* station);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::MonitorStationEditDialog *ui;
    MonitorStation* station;
};

#endif // MONITORSTATION_EDIT_DIALOG_H
