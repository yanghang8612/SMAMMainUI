#include <QtGlobal>
#include <QGraphicsView>
#include <QCloseEvent>
#include <QDebug>

#include "stationmonitor_widget.h"
#include "ui_stationmonitor_widget.h"

#include "common.h"
#include "utilities/config_helper.h"

StationMonitorWidget::StationMonitorWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::StationMonitorWidget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-490, -205, 980, 410);
    stateWidget = new DataTransferStateFrame(this);
    stateWidget->setGeometry(670, 10, 310, 80);
    stateWidget->hide();
    //ui->monitorView->resize(996, 444);
    ui->monitorView->setScene(scene);
    ui->monitorView->setCacheMode(QGraphicsView::CacheBackground);
    ui->monitorView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    ui->monitorView->setRenderHint(QPainter::Antialiasing);

    initView();
}

StationMonitorWidget::~StationMonitorWidget()
{
    delete ui;
}

void StationMonitorWidget::updateView()
{
    if (ConfigHelper::monitorStations.size() > monitorNodeList.size()) {
        int index = ConfigHelper::monitorStations.size() - 1;
        MonitorNode* stationNode = new MonitorNode(ConfigHelper::monitorStations[index], 35, stateWidget, this);
        scene->addItem(stationNode);
        monitorNodeList << stationNode;
    }
    if (ConfigHelper::monitorStations.size() < monitorNodeList.size()) {
        for (int i = 0; i < monitorNodeList.size(); i++) {
            if (monitorNodeList[i]->getStation()->getMemID() == 0) {
                scene->removeItem(monitorNodeList[i]);
                delete monitorNodeList[i];
                monitorNodeList.removeAt(i);
            }
        }
    }
    updateMonitorNodeList();
    scene->update();
}

void StationMonitorWidget::initView()
{
    for (int i = 0; i < ConfigHelper::monitorStations.size(); i++) {
        MonitorNode* stationNode = new MonitorNode(ConfigHelper::monitorStations[i], 35, stateWidget, this);
        scene->addItem(stationNode);
        monitorNodeList << stationNode;
    }
    updateMonitorNodeList();
}

void StationMonitorWidget::updateMonitorNodeList()
{
    qreal stationLength = 60;
    QPointF startStationPoint(-450, -170);
    for (int i = 0; i < monitorNodeList.size(); i++) {
        monitorNodeList[i]->setPos(startStationPoint + QPointF((i / 6) * stationLength, (stationLength + 5) * (i % 6)));
        monitorNodeList[i]->updateStateNode();
    }
}
