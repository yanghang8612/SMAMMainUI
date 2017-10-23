#ifndef MAINMONITOR_WIDGET_H
#define MAINMONITOR_WIDGET_H

#include <QTabWidget>
#include <QGraphicsScene>

#include "other_component_header.h"
#include "item/receivernode.h"
#include "item/standardnode.h"
#include "item/igmasnode.h"
#include "item/maincenternode.h"
#include "item/othercenternode.h"
#include "item/filenode.h"
#include "item/harddrivenode.h"
#include "item/usersnode.h"

namespace Ui {
class MainMonitorWidget;
}

class MainMonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit MainMonitorWidget(QWidget* parent = 0);
    ~MainMonitorWidget();

    void updateView();

private:
    Ui::MainMonitorWidget* ui;
    QGraphicsScene* scene;
    QList<StandardNode*> stationNodeList;
    QList<ReceiverNode*> receiverNodeList;
    QList<iGMASNode*> iGMASNodeList;
    QList<OtherCenterNode*> otherCenterNodeList;

    void updateDeviceConnectState();
    void updateXJView();
    void updateBJView();
};

#endif // MAINMONITOR_WIDGET_H
