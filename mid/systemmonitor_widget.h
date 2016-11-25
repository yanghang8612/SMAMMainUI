#ifndef SYSTEMMONITOR_WIDGET_H
#define SYSTEMMONITOR_WIDGET_H

#include <QWidget>

namespace Ui {
	class SystemMonitorWidget;
}

class SystemMonitorWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SystemMonitorWidget(QWidget *parent = 0);
	~SystemMonitorWidget();

private:
	Ui::SystemMonitorWidget *ui;
};

#endif // SYSTEMMONITOR_WIDGET_H
