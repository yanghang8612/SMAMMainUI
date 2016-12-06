#include <QGraphicsView>
#include <QDebug>

#include "mainmonitor_widget.h"
#include "ui_mainmonitor_widget.h"
#include "graphicsitem/receivernode.h"
#include "graphicsitem/stationnode.h"
#include "graphicsitem/centernode.h"
#include "graphicsitem/edge.h"

MainMonitorWidget::MainMonitorWidget(const QList<StandardStation *> &standardStationList, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::MainMonitorWidget), standardStationList(standardStationList)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-500, -235, 1000, 470);
    //ui->monitorView->resize(1000, 470);
    ui->monitorView->setScene(scene);
    ui->monitorView->setCacheMode(QGraphicsView::CacheBackground);
    ui->monitorView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->monitorView->setRenderHint(QPainter::Antialiasing);
    ui->monitorView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    updateView();
}

MainMonitorWidget::~MainMonitorWidget()
{
    delete ui;
}

void MainMonitorWidget::updateView()
{
    CenterNode* centerNode = new CenterNode();
    centerNode->setPos(400, 0);
    scene->addItem(centerNode);

    int stationCount = standardStationList.size();
    QPointF topStationPoint(0, -100 * (stationCount - 1));
    for (int i = 0; i < stationCount; i++) {
        StandardStation* station = standardStationList.at(i);
        StationNode* stationNode = new StationNode(station);
        stationNode->setPos(topStationPoint + QPointF(0, 200 * i));
        stationNode->setStatus(1);
        scene->addItem(stationNode);
        scene->addItem(new Edge(stationNode, centerNode));

        int receiverCount = station->getReceivers().size();
        QPointF topReceiverPoint(-400, stationNode->pos().y() - 50 * (receiverCount - 1) - 1);
        for (int j = 0; j < receiverCount; j++) {
            Receiver* receiver = station->getReceivers().at(j);
            ReceiverNode* receiverNode = new ReceiverNode(receiver);
            receiverNode->setPos(topReceiverPoint + QPointF(0, 100 * j));
            if (i == 1) {
                receiverNode->setStatus(1);
            }
            else {
                receiverNode->setStatus(2);
            }
            scene->addItem(receiverNode);
            scene->addItem(new Edge(receiverNode, stationNode));
        }
    }
}

void MainMonitorWidget::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    emit closeMessage();
}
