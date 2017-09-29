#ifndef MAINMONITOR_WIDGET_H
#define MAINMONITOR_WIDGET_H

#include <QTabWidget>
#include <QGraphicsScene>

#include "other_component_header.h"
#include "utilities/shared_buffer.h"
#include "bean/standard_station.h"
#include "bean/igmas_station.h"
#include "bean/other_center.h"
#include "item/receivernode.h"
#include "item/standardnode.h"
#include "item/igmasnode.h"
#include "item/centernode.h"
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

private slots:
    void updateDeviceConnectState();
    void updateDeviceTransferState();

private:
    Ui::MainMonitorWidget* ui;
    QGraphicsScene* scene;
    QList<StandardNode*> stationNodeList;
    QList<ReceiverNode*> receiverNodeList;
    QList<iGMASNode*> iGMASNodeList;
    QList<CenterNode*> otherCenterNodeList;
    SharedBuffer* receiverStateSharedBuffer;
    SharedBuffer* iGMASStateSharedBuffer;
    SharedBuffer* otherCenterStateSharedBuffer;
    ReceiverState receiverState[RECEIVER_MAXITEMCOUNT];
    IGMASState iGMASState[IGMASSTATION_MAXITEMCOUNT];
    OtherCenterState otherCenterState[OTHERCENTER_MAXITEMCOUNT];

    QTimer* deviceConnectStateCheckTimer;
    QTimer* deviceTransferStateCheckTimer;

    void updateXJView();
    void updateBJView();
};

#endif // MAINMONITOR_WIDGET_H
