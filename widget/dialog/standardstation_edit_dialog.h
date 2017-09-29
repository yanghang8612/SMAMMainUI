#ifndef STANDARDSTATION_EDIT_DIALOG_H
#define STANDARDSTATION_EDIT_DIALOG_H

#include <QDialog>

#include "bean/standard_station.h"

namespace Ui {
class StandardStationEditDialog;
}

class StandardStationEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StandardStationEditDialog(QWidget *parent = 0);
    explicit StandardStationEditDialog(StandardStation* station, QWidget *parent = 0);
    ~StandardStationEditDialog();

signals:
    void confirmButtonClicked(StandardStation* station);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::StandardStationEditDialog *ui;
    StandardStation* station;
};

#endif // STANDARDSTATION_EDIT_DIALOG_H
