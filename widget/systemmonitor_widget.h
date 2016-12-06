#ifndef SYSTEMMONITOR_WIDGET_H
#define SYSTEMMONITOR_WIDGET_H

#include <QWidget>

#include "station/standard_station.h"

namespace Ui {
	class SystemMonitorWidget;
}

class SystemMonitorWidget : public QWidget
{
	Q_OBJECT

public:
    SystemMonitorWidget(const QList<StandardStation*>& standardStationList, QWidget *parent = 0);
	~SystemMonitorWidget();

private:
    void updateView();

private slots:
    void closeEvent(QCloseEvent* closeEvent);

signals:
    void closeMessage();

private:
	Ui::SystemMonitorWidget *ui;
    QList<StandardStation*> standardStationList;
	QGraphicsScene* scene;
};

#endif // SYSTEMMONITOR_WIDGET_H
