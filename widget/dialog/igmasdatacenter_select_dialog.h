#ifndef IGMASDATACENTER_SELECT_DIALOG_H
#define IGMASDATACENTER_SELECT_DIALOG_H

#include <QDialog>

namespace Ui {
class iGMASDataCenterSelectDialog;
}

class iGMASDataCenterSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit iGMASDataCenterSelectDialog(const QString& dataCenters, QWidget *parent = 0);
    ~iGMASDataCenterSelectDialog();

signals:
    void confirmButtonClicked(QString newDataCenters);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::iGMASDataCenterSelectDialog *ui;
};

#endif // IGMASDATACENTER_SELECT_DIALOG_H
