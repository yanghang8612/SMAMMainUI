#ifndef DATACENTER_EDIT_DIALOG_H
#define DATACENTER_EDIT_DIALOG_H

#include <QDialog>

#include "bean/data_center.h"

namespace Ui {
class DataCenterEditDialog;
}

class DataCenterEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataCenterEditDialog(QWidget *parent = 0);
    explicit DataCenterEditDialog(DataCenter* dataCenter, QWidget *parent = 0);
    ~DataCenterEditDialog();

signals:
    void confirmButtonClicked(DataCenter* dataCenter);

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::DataCenterEditDialog *ui;

    DataCenter* dataCenter;
};

#endif // DATACENTER_EDIT_DIALOG_H
