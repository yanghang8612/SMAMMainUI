#ifndef IGMASSTATION_EDIT_DIALOG_H
#define IGMASSTATION_EDIT_DIALOG_H

#include <QDialog>

#include "bean/igmas_station.h"

namespace Ui {
class iGMASStationEditDialog;
}

class iGMASStationEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit iGMASStationEditDialog(QWidget *parent = 0);
    explicit iGMASStationEditDialog(iGMASStation* station, QWidget *parent = 0);
    ~iGMASStationEditDialog();

signals:
    void confirmButtonClicked(iGMASStation* station);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::iGMASStationEditDialog *ui;
    iGMASStation* station;
};

#endif // IGMASSTATION_EDIT_DIALOG_H
