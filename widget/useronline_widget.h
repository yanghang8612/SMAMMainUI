#ifndef USERONLINE_WIDGET_H
#define USERONLINE_WIDGET_H

#include <QTabWidget>

#include "db/database_access.h"
#include "user/base_user.h"

namespace Ui {
	class UserOnlineWidget;
}

class UserOnlineWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit UserOnlineWidget(QWidget *parent = 0);
	~UserOnlineWidget();

protected:
	void timerEvent(QTimerEvent* event);

private:
	Ui::UserOnlineWidget *ui;
	const QString dbName;
	QSqlRelationalTableModel* data;
	QList<QString> colunmName;

	void updateTable();

};

#endif // USERONLINE_WIDGET_H
