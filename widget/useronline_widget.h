#ifndef USERONLINE_WIDGET_H
#define USERONLINE_WIDGET_H

#include <QTabWidget>

namespace Ui {
	class UserOnlineWidget;
}

class UserOnlineWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit UserOnlineWidget(QWidget *parent = 0);
	~UserOnlineWidget();

private:
	Ui::UserOnlineWidget *ui;
};

#endif // USERONLINE_WIDGET_H
