#ifndef MAINMONITOR_WIDGET_H
#define MAINMONITOR_WIDGET_H

#include <QTabWidget>

#include "bean/station/standard_station.h"
#include "bean/center/other_center.h"

namespace Ui {
class MainMonitorWidget;
}

class MainMonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit MainMonitorWidget(const QList<StandardStation*>& standardStationList, const QList<OtherCenter*>& otherCenterList, QWidget* parent = 0);
    ~MainMonitorWidget();

    void updateView();

private slots:
    void closeEvent(QCloseEvent* closeEvent);

signals:
    void closeMessage();

private:
    Ui::MainMonitorWidget* ui;
    const QList<StandardStation*>& standardStationList;
    const QList<OtherCenter*>& otherCenterList;
    QGraphicsScene* scene;
};

#endif // MAINMONITOR_WIDGET_H
