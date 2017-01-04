#ifndef MODIFY_USER_DIALOG_H
#define MODIFY_USER_DIALOG_H

#include <QDialog>

#include "bean/center/other_center.h"

namespace Ui {
    class ModifyCenterDialog;
}

class ModifyCenterDialog : public QDialog
{
	Q_OBJECT

public:
    explicit ModifyCenterDialog(OtherCenter* center, QWidget *parent = 0);
    ~ModifyCenterDialog();

signals:
    void confirmButtonClicked(OtherCenter* center);

private slots:
	void on_confirmButton_clicked();
	void on_cancelButton_clicked();

private:
    Ui::ModifyCenterDialog *ui;
    OtherCenter* center;
};

#endif // MODIFY_USER_DIALOG_H
