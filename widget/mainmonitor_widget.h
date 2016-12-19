#ifndef MAINMONITOR_WIDGET_H
#define MAINMONITOR_WIDGET_H

#include <QTabWidget>

#include "station/standard_station.h"

namespace Ui {
class MainMonitorWidget;
}

class MainMonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit MainMonitorWidget(QList<StandardStation*>* standardStationList, QWidget *parent = 0);
    ~MainMonitorWidget();

    void updateView();

private slots:
    void closeEvent(QCloseEvent* closeEvent);

signals:
    void closeMessage();

private:
    Ui::MainMonitorWidget *ui;
    QList<StandardStation*>* standardStationList;
    QGraphicsScene* scene;
};

#endif // MAINMONITOR_WIDGET_H
