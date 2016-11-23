#ifndef ADD_USER_DIALOG_H
#define ADD_USER_DIALOG_H

#include <QDialog>

namespace Ui {
	class AddUserDialog;
}

class AddUserDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddUserDialog(QWidget *parent = 0);
	~AddUserDialog();

private:
	Ui::AddUserDialog *ui;
};

#endif // ADD_USER_DIALOG_H
