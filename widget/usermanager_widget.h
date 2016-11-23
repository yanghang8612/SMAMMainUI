#ifndef USERMANAGER_WIDGET_H
#define USERMANAGER_WIDGET_H

#include <QTabWidget>

#include "db/database_access.h"
#include "user/base_user.h"

namespace Ui {
	class UserManagerWidget;
}

class UserManagerWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit UserManagerWidget(QWidget *parent = 0);
	~UserManagerWidget();

private slots:
	void showRightMenu(QPoint pos);

	void showAddNewUserDialog();
	void addNewUser(BaseUser* user);

	void showModifyUserDialog();
	void modifyUser(BaseUser* user);

	void deleteUser();
	void showViewUserDialog();

private:
	Ui::UserManagerWidget *ui;
	const QString dbName = "UserManager";
	QSqlTableModel* data = 0;
	QList<QString> colunmName;

	void updateTable();
};

#endif // USERMANAGER_WIDGET_H
