#ifndef OTHERCENTER_EDIT_DIALOG_H
#define OTHERCENTER_EDIT_DIALOG_H

#include <QDialog>

#include "bean/other_center.h"

namespace Ui {
class OtherCenterEditDialog;
}

class OtherCenterEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OtherCenterEditDialog(QWidget *parent = 0);
    explicit OtherCenterEditDialog(OtherCenter* center, QWidget *parent = 0);
    ~OtherCenterEditDialog();

signals:
    void confirmButtonClicked(OtherCenter* center);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::OtherCenterEditDialog *ui;
    OtherCenter* center;
};

#endif // OTHERCENTER_EDIT_DIALOG_H
