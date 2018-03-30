#include <QtGlobal>
#include <QGraphicsView>
#include <QCloseEvent>
#include <QDebug>

#include "receivermonitor_widget.h"
#include "ui_receivermonitor_widget.h"

#include "common.h"
#include "utilities/config_helper.h"

ReceiverMonitorWidget::ReceiverMonitorWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ReceiverMonitorWidget)
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

ReceiverMonitorWidget::~ReceiverMonitorWidget()
{
    delete ui;
}

void ReceiverMonitorWidget::updateView()
{

}

void ReceiverMonitorWidget::initView()
{
    MainCenterNode* mainCenterNode = new MainCenterNode(new MainCenter(tr("新疆中心")), 50);
    mainCenterNode->setPos(0, 0);
    scene->addItem(mainCenterNode);

    TerminalNode* usersNode = new TerminalNode(45);
    usersNode->setPos(0, -150);
    scene->addItem(usersNode);
    scene->addItem(new Edge(mainCenterNode, usersNode));

    FileNode* fileNode = new FileNode(40);
    fileNode->setPos(0, 150);
    scene->addItem(fileNode);
    scene->addItem(new Edge(mainCenterNode, fileNode));

    int stationCount = ConfigHelper::standardStations.size();
    if (0 == stationCount) {
        return;
    }
    qreal stationLength = qMin((double) 400 / stationCount, 100.0);

    QPointF topStationPoint(-200, - stationLength / 2 * (stationCount - 1));
    for (int i = 0; i < stationCount; i++) {
        StandardStation* station = ConfigHelper::standardStations[i];
        StandardNode* stationNode = new StandardNode(station, stationLength * 0.5);
        stationNode->setPos(topStationPoint + QPointF(0, stationLength * i));
        scene->addItem(stationNode);
        scene->addItem(new Edge(stationNode, mainCenterNode));
        stationNodeList << stationNode;

        int receiverCount = station->getReceivers().size();
        QPointF topReceiverPoint(-200 - stationLength * 0.55, stationNode->pos().y());
        for (int j = 0; j < receiverCount; j++) {
            Receiver* receiver = station->getReceivers().at(j);
            ReceiverNode* receiverNode = new ReceiverNode(receiver, stationLength * 0.4);
            receiverNode->setPos(topReceiverPoint - QPointF(stationLength * 0.7 * j, 0));
            scene->addItem(receiverNode);
            receiverNodeList << receiverNode;
        }
    }
}

void ReceiverMonitorWidget::updateReceiverNodeList()
{

}
