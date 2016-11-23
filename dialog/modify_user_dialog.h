#ifndef MODIFY_USER_DIALOG_H
#define MODIFY_USER_DIALOG_H

#include <QDialog>

namespace Ui {
	class ModifyUserDialog;
}

class ModifyUserDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ModifyUserDialog(QWidget *parent = 0);
	~ModifyUserDialog();

private:
	Ui::ModifyUserDialog *ui;
};

#endif // MODIFY_USER_DIALOG_H
