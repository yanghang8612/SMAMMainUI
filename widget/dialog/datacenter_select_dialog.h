#ifndef DATACENTER_SELECT_DIALOG_H
#define DATACENTER_SELECT_DIALOG_H

#include <QDialog>

namespace Ui {
class DataCenterSelectDialog;
}

class DataCenterSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataCenterSelectDialog(const QString& dataCenters, QWidget *parent = 0);
    ~DataCenterSelectDialog();

signals:
    void confirmButtonClicked(QString newDataCenters);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::DataCenterSelectDialog *ui;
};

#endif // DATACENTER_SELECT_DIALOG_H
