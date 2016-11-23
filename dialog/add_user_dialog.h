#ifndef ADD_USER_DIALOG_H
#define ADD_USER_DIALOG_H

#include <QDialog>

#include "user/base_user.h"

namespace Ui {
	class AddUserDialog;
}

class AddUserDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddUserDialog(QWidget *parent = 0);
	~AddUserDialog();

signals:
	void confirmButtonClicked(BaseUser* user);

private slots:
	void on_confirmButton_clicked();

	void on_cancelButton_clicked();

private:
	Ui::AddUserDialog *ui;
};

#endif // ADD_USER_DIALOG_H
