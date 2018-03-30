#ifndef MAINMONITOR_WIDGET_H
#define MAINMONITOR_WIDGET_H

#include <QTabWidget>
#include <QGraphicsScene>

#include "other_component_header.h"
#include "item/maincenternode.h"
#include "item/othercenternode.h"
#include "item/terminalnode.h"
#include "../popup/datatransferstate_frame.h"

namespace Ui {
    class CenterMonitorWidget;
}

class CenterMonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit CenterMonitorWidget(QWidget* parent = 0);
    ~CenterMonitorWidget();

    void updateView();

private:
    Ui::CenterMonitorWidget* ui;
    QGraphicsScene* scene;
    MainCenterNode* mainCenterNode;
    QList<OtherCenterNode*> otherCenterNodeList;
    QList<TerminalNode*> terminalNodeList;

    void initView();
    void updateOtherCenterNodeList();
};

#endif // MAINMONITOR_WIDGET_H
