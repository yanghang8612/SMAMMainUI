#ifndef RECEIVERMONITOR_WIDGET_H
#define RECEIVERMONITOR_WIDGET_H

#include <QTabWidget>
#include <QGraphicsScene>

#include "other_component_header.h"
#include "item/filenode.h"
#include "item/maincenternode.h"
#include "item/receivernode.h"
#include "item/standardnode.h"
#include "item/terminalnode.h"
#include "../popup/datatransferstate_frame.h"

namespace Ui {
    class ReceiverMonitorWidget;
}

class ReceiverMonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit ReceiverMonitorWidget(QWidget *parent = 0);
    ~ReceiverMonitorWidget();

    void updateView();

private:
    Ui::ReceiverMonitorWidget *ui;
    QGraphicsScene* scene;
    MainCenterNode* mainCenterNode;
    DataTransferStateFrame* stateWidget;
    QList<StandardNode*> stationNodeList;
    QList<ReceiverNode*> receiverNodeList;

    void initView();
    void updateReceiverNodeList();
};

#endif // RECEIVERMONITOR_WIDGET_H
