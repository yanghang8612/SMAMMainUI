#ifndef MAINMONITOR_WIDGET_H
#define MAINMONITOR_WIDGET_H

#include <QTabWidget>
#include <QGraphicsScene>

#include "bean/station/standard_station.h"
#include "bean/station/igmas_station.h"
#include "bean/center/other_center.h"

namespace Ui {
class MainMonitorWidget;
}

class MainMonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit MainMonitorWidget(const QList<StandardStation*>* const standardStationList, const QList<OtherCenter*>* const otherCenterList, QWidget* parent = 0);
    explicit MainMonitorWidget(const QList<IGMASStation*>* const iGMASStationList, const QList<OtherCenter*>* const otherCenterList, QWidget* parent = 0);
    ~MainMonitorWidget();

    void updateView();

private slots:
    void closeEvent(QCloseEvent* closeEvent);

signals:
    void closeMessage();

private:
    Ui::MainMonitorWidget* ui;
    const QList<StandardStation*>* const standardStationList;
    const QList<IGMASStation*>* const iGMASStationList;
    const QList<OtherCenter*>* const otherCenterList;
    QGraphicsScene* scene;

    void init();
    void updateXJView();
    void updateBJView();
};

#endif // MAINMONITOR_WIDGET_H
