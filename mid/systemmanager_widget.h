#ifndef SYSTEMMANAGER_WIDGET_H
#define SYSTEMMANAGER_WIDGET_H

#include <QWidget>

namespace Ui {
	class SystemManagerWidget;
}

class SystemManagerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SystemManagerWidget(QWidget *parent = 0);
	~SystemManagerWidget();

private:
	Ui::SystemManagerWidget *ui;
};

#endif // SYSTEMMANAGER_WIDGET_H
