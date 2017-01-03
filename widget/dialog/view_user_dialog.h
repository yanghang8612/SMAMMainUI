#ifndef VIEW_USER_DIALOG_H
#define VIEW_USER_DIALOG_H

#include <QDialog>

#include "bean/user/base_user.h"

namespace Ui {
	class ViewUserDialog;
}

class ViewUserDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ViewUserDialog(QWidget *parent = 0);
	~ViewUserDialog();

private:
	Ui::ViewUserDialog *ui;
};

#endif // VIEW_USER_DIALOG_H
