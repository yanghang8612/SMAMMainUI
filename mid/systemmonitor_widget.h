#ifndef SYSTEMMONITOR_WIDGET_H
#define SYSTEMMONITOR_WIDGET_H

#include <QWidget>

#include "widget/treewidget/smam_treewidget.h"

namespace Ui {
	class SystemMonitorWidget;
}

class SystemMonitorWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SystemMonitorWidget(QWidget *parent = 0, SMAMTreeWidget* treeWidget = 0);
	~SystemMonitorWidget();

private:
	void updateView();

private:
	Ui::SystemMonitorWidget *ui;
	SMAMTreeWidget* treeWidget;
	QGraphicsScene* scene;
};

#endif // SYSTEMMONITOR_WIDGET_H
