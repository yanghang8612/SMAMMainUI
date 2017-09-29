#ifndef IGMASDATACENTER_EDIT_DIALOG_H
#define IGMASDATACENTER_EDIT_DIALOG_H

#include <QDialog>

#include "bean/igmas_datacenter.h"

namespace Ui {
class iGMASDataCenterEditDialog;
}

class iGMASDataCenterEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit iGMASDataCenterEditDialog(QWidget *parent = 0);
    explicit iGMASDataCenterEditDialog(iGMASDataCenter* dataCenter, QWidget *parent = 0);
    ~iGMASDataCenterEditDialog();

signals:
    void confirmButtonClicked(iGMASDataCenter* dataCenter);

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::iGMASDataCenterEditDialog *ui;

    iGMASDataCenter* dataCenter;
};

#endif // IGMASDATACENTER_EDIT_DIALOG_H
