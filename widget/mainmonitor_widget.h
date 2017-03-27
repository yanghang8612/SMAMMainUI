#ifndef MAINMONITOR_WIDGET_H
#define MAINMONITOR_WIDGET_H

#include <QTabWidget>
#include <QGraphicsScene>

#include "utilies/shared_buffer.h"
#include "widget/treewidget/smam_treewidget.h"
#include "bean/station/standard_station.h"
#include "bean/station/igmas_station.h"
#include "bean/center/other_center.h"
#include "graphicsitem/receivernode.h"
#include "graphicsitem/stationnode.h"
#include "graphicsitem/centernode.h"
#include "graphicsitem/filenode.h"
#include "graphicsitem/harddrivenode.h"
#include "graphicsitem/usersnode.h"

struct ReceiverState {
    char ipAddress[16];
    bool isConnected;
};

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

protected:
    void timerEvent(QTimerEvent* event);

private:
    Ui::MainMonitorWidget* ui;
    const QList<StandardStation*>& standardStationList;
    const QList<IGMASStation*>& iGMASStationList;
    const QList<OtherCenter*>& otherCenterList;
    QGraphicsScene* scene;
    QList<StationNode*> stationNodeList;
    QList<ReceiverNode*> receiverNodeList;
    QList<CenterNode*> centerNodeList;
    SharedBuffer* receiverStateSharedBuffer;
    ReceiverState receiverState[RECEIVER_SHAREDBUFFER_MAXITEMCOUNT];

    void updateXJView();
    void updateBJView();
};

#endif // MAINMONITOR_WIDGET_H
