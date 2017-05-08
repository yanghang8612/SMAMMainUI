#ifndef MAINMONITOR_WIDGET_H
#define MAINMONITOR_WIDGET_H

#include <QTabWidget>
#include <QGraphicsScene>

#include "other_component_header.h"
#include "utilies/shared_buffer.h"
#include "bean/station/standard_station.h"
#include "bean/station/igmas_station.h"
#include "bean/center/other_center.h"
#include "widget/treewidget/smam_treewidget.h"
#include "graphicsitem/receivernode.h"
#include "graphicsitem/standardnode.h"
#include "graphicsitem/igmasnode.h"
#include "graphicsitem/centernode.h"
#include "graphicsitem/filenode.h"
#include "graphicsitem/harddrivenode.h"
#include "graphicsitem/usersnode.h"
#include "graphicsitem/dmznode.h"

namespace Ui {
class MainMonitorWidget;
}

class MainMonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit MainMonitorWidget(SMAMTreeWidget* treeWidget, QWidget* parent = 0);
    ~MainMonitorWidget();

    void updateView();

private slots:
    void updateDeviceConnectState();
    void updateDeviceTransferState();

private:
    Ui::MainMonitorWidget* ui;
    const QList<StandardStation*>& standardStationList;
    const QList<IGMASStation*>& iGMASStationList;
    const QList<OtherCenter*>& otherCenterList;
    QGraphicsScene* scene;
    QList<StandardNode*> stationNodeList;
    QList<ReceiverNode*> receiverNodeList;
    QList<IGMASNode*> iGMASNodeList;
    QList<CenterNode*> otherCenterNodeList;
    SharedBuffer* receiverStateSharedBuffer;
    SharedBuffer* iGMASStateSharedBuffer;
    SharedBuffer* otherCenterStateSharedBuffer;
    ReceiverState receiverState[RECEIVER_SHAREDBUFFER_MAXITEMCOUNT];
    IGMASState iGMASState[IGMAS_STATE_SHAREDBUFFER_MAXITEMCOUNT];
    OtherCenterState otherCenterState[OTHERCENTER_STATE_SHAREDBUFFER_MAXITEMCOUNT];

    QTimer* deviceConnectStateCheckTimer;
    QTimer* deviceTransferStateCheckTimer;

    void updateXJView();
    void updateDMZView();
    void updateBJView();
};

#endif // MAINMONITOR_WIDGET_H
