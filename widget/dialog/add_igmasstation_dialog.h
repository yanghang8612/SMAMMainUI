#ifndef ADD_IGMASSTATION_DIALOG_H
#define ADD_IGMASSTATION_DIALOG_H

#include <QDialog>

#include "bean/station/igmas_station.h"

namespace Ui {
class AddIGMASStationDialog;
}

class AddIGMASStationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddIGMASStationDialog(QWidget *parent = 0);
    ~AddIGMASStationDialog();

signals:
    void confirmButtonClicked(IGMASStation* station);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::AddIGMASStationDialog *ui;
};

#endif // ADD_IGMASSTATION_DIALOG_H
