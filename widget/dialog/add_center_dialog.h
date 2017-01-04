#ifndef ADD_USER_DIALOG_H
#define ADD_USER_DIALOG_H

#include <QDialog>

#include "bean/center/other_center.h"

namespace Ui {
    class AddCenterDialog;
}

class AddCenterDialog : public QDialog
{
	Q_OBJECT

public:
    explicit AddCenterDialog(QWidget *parent = 0);
    ~AddCenterDialog();

signals:
    void confirmButtonClicked(OtherCenter* center);

private slots:
	void on_confirmButton_clicked();
	void on_cancelButton_clicked();

private:
    Ui::AddCenterDialog *ui;
};

#endif // ADD_USER_DIALOG_H
