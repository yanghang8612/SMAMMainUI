#ifndef MODIFY_USER_DIALOG_H
#define MODIFY_USER_DIALOG_H

#include <QDialog>

#include "bean/user/base_user.h"

namespace Ui {
	class ModifyUserDialog;
}

class ModifyUserDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ModifyUserDialog(QWidget *parent = 0, BaseUser* user = 0);
	~ModifyUserDialog();

signals:
	void confirmButtonClicked(BaseUser* user);

private slots:
	void on_confirmButton_clicked();
	void on_cancelButton_clicked();

private:
	Ui::ModifyUserDialog *ui;
	BaseUser* user;
};

#endif // MODIFY_USER_DIALOG_H
