#ifndef MODIFY_IGMASSTATION_DIALOG_H
#define MODIFY_IGMASSTATION_DIALOG_H

#include <QDialog>

#include "bean/station/igmas_station.h"

namespace Ui {
    class ModifyIGMASStationDialog;
}

class ModifyIGMASStationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyIGMASStationDialog(IGMASStation* station, QWidget *parent = 0);
    ~ModifyIGMASStationDialog();

signals:
    void confirmButtonClicked(IGMASStation* station);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ModifyIGMASStationDialog *ui;
    IGMASStation* station;
};

#endif // MODIFY_IGMASSTATION_DIALOG_H
