#ifndef USERMANAGER_WIDGET_H
#define USERMANAGER_WIDGET_H

#include <QTabWidget>

namespace Ui {
	class UserManagerWidget;
}

class UserManagerWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit UserManagerWidget(QWidget *parent = 0);
	~UserManagerWidget();

private:
	Ui::UserManagerWidget *ui;
};

#endif // USERMANAGER_WIDGET_H
