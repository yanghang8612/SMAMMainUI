#include <QGraphicsView>
#include <QDebug>

#include "mainmonitor_widget.h"
#include "ui_mainmonitor_widget.h"
#include "graphicsitem/receivernode.h"
#include "graphicsitem/stationnode.h"
#include "graphicsitem/centernode.h"
#include "graphicsitem/filenode.h"
#include "graphicsitem/harddrivenode.h"
#include "graphicsitem/usersnode.h"
#include "graphicsitem/edge.h"

MainMonitorWidget::MainMonitorWidget(QList<StandardStation*>* standardStationList, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::MainMonitorWidget), standardStationList(standardStationList)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-490, -210, 980, 420);
    ui->monitorView->resize(996, 444);
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
    scene->clear();

    CenterNode* centerNode = new CenterNode(60);
    centerNode->setPos(200, 0);
    scene->addItem(centerNode);

    UsersNode* usersNode = new UsersNode(60);
    usersNode->setPos(400, 0);
    scene->addItem(usersNode);
    scene->addItem(new Edge(centerNode, usersNode));

    FileNode* fileNode = new FileNode(40);
    fileNode->setPos(200, 150);
    scene->addItem(fileNode);
    scene->addItem(new Edge(centerNode, fileNode));

    HardDriveNode* hardDriveNode = new HardDriveNode(40);
    hardDriveNode->setPos(400, 150);
    scene->addItem(hardDriveNode);
    scene->addItem(new Edge(fileNode, hardDriveNode));

    int stationCount = standardStationList->size();
    if (0 == stationCount) {
        return;
    }
    qreal stationLength = 400 / stationCount;

    int maxReceiverCount = 1;
    qreal receiverLength = 0;

    for (int i = 0; i < stationCount; i++) {
        int receiverCount = standardStationList->at(i)->getReceivers().size();
        maxReceiverCount = (receiverCount > maxReceiverCount) ? receiverCount : maxReceiverCount;
    }
    receiverLength = stationLength / maxReceiverCount;

    QPointF topStationPoint(-100, - stationLength / 2 * (stationCount - 1));
    for (int i = 0; i < stationCount; i++) {
        StandardStation* station = standardStationList->at(i);
        StationNode* stationNode = new StationNode(station, stationLength * 0.5);
        stationNode->setPos(topStationPoint + QPointF(0, stationLength * i));
        stationNode->setStatus(1);
        scene->addItem(stationNode);
        scene->addItem(new Edge(stationNode, centerNode));

        int receiverCount = station->getReceivers().size();
        QPointF topReceiverPoint(-400, stationNode->pos().y() - receiverLength / 2 * (receiverCount - 1));
        for (int j = 0; j < receiverCount; j++) {
            Receiver* receiver = station->getReceivers().at(j);
            ReceiverNode* receiverNode = new ReceiverNode(receiver, receiverLength * 0.8);
            receiverNode->setPos(topReceiverPoint + QPointF(0, receiverLength * j));
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
