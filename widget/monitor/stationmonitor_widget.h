#ifndef STATIONMONITOR_WIDGET_H
#define STATIONMONITOR_WIDGET_H

#include <QTabWidget>
#include <QGraphicsScene>

#include "other_component_header.h"
#include "item/monitornode.h"
#include "../popup/datatransferstate_frame.h"

namespace Ui {
    class StationMonitorWidget;
}

class StationMonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit StationMonitorWidget(QWidget *parent = 0);
    ~StationMonitorWidget();

    void updateView();

private:
    Ui::StationMonitorWidget *ui;
    QGraphicsScene* scene;
    DataTransferStateFrame* stateWidget;
    QList<MonitorNode*> monitorNodeList;

    void initView();
    void updateMonitorNodeList();
};

#endif // STATIONMONITOR_WIDGET_H
