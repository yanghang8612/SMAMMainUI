#include <QtGlobal>
#include <QGraphicsView>
#include <QCloseEvent>
#include <QDebug>

#include "common.h"
#include "mainmonitor_widget.h"
#include "ui_mainmonitor_widget.h"
#include "graphicsitem/edge.h"

extern DeploymentType::Value deploymentType;
extern void* receiverStateSharedBufferPointer;

MainMonitorWidget::MainMonitorWidget(SMAMTreeWidget* treeWidget, QWidget* parent) :
    QTabWidget(parent),
    ui(new Ui::MainMonitorWidget),
    standardStationList(treeWidget->getStandardStationList()),
    iGMASStationList(treeWidget->getIGMASStationList()),
    otherCenterList(treeWidget->getOtherCenterList()),
    receiverStateSharedBuffer(0)
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

    startTimer(RECEIVER_STATE_CHECK_TIMEINTERVAL);
    updateView();
}

MainMonitorWidget::~MainMonitorWidget()
{
    delete ui;
}

void MainMonitorWidget::updateView() {
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            updateXJView();
            break;
        case DeploymentType::BJ_CENTER:
            updateBJView();
            break;
        default:
            break;
    }
}

void MainMonitorWidget::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    if (receiverStateSharedBuffer == 0) {
        receiverStateSharedBuffer = (receiverStateSharedBufferPointer == 0) ? 0 : new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                                                                                   SharedBuffer::ONLY_READ,
                                                                                                   receiverStateSharedBufferPointer,
                                                                                                   sizeof(ReceiverState));
    }
    else {
        receiverStateSharedBuffer->readData((void*) receiverState);
        for (int i = 0; i < receiverNodeList.size(); i++) {
            for (int j = 0; j < receiverStateSharedBuffer->getItemCount(); j++) {
                if (qstrcmp(receiverNodeList[i]->getReceiverIPAddress().toStdString().c_str(), receiverState[j].ipAddress) == 0)
                    receiverNodeList[i]->setStatus(receiverState[j].isConnected ? 1 : 2);
            }
        }
    }
}

void MainMonitorWidget::updateXJView()
{
    scene->clear();

    CenterNode* centerNode = new CenterNode(60, tr("新疆中心"));
    centerNode->setPos(200, 0);
    scene->addItem(centerNode);

    UsersNode* usersNode = new UsersNode(50);
    usersNode->setPos(200, -150);
    scene->addItem(usersNode);
    scene->addItem(new Edge(centerNode, usersNode));

    FileNode* fileNode = new FileNode(40);
    fileNode->setPos(200, 150);
    scene->addItem(fileNode);
    scene->addItem(new Edge(centerNode, fileNode));

    HardDriveNode* hardDriveNode = new HardDriveNode(40);
    hardDriveNode->setPos(300, 150);
    scene->addItem(hardDriveNode);
    scene->addItem(new Edge(fileNode, hardDriveNode));

    int stationCount = standardStationList.size();
    if (0 == stationCount) {
        return;
    }
    qreal stationLength = qMin((double) 400 / stationCount, 100.0);

    int maxReceiverCount = 1;
    qreal receiverLength = 0;

    for (int i = 0; i < stationCount; i++) {
        int receiverCount = standardStationList[i]->getReceivers().size();
        maxReceiverCount = (receiverCount > maxReceiverCount) ? receiverCount : maxReceiverCount;
    }
    receiverLength = qMin(stationLength / maxReceiverCount, 60.0);

    QPointF topStationPoint(-100, - stationLength / 2 * (stationCount - 1));
    for (int i = 0; i < stationCount; i++) {
        StandardStation* station = standardStationList[i];
        StationNode* stationNode = new StationNode(station, stationLength * 0.5);
        stationNode->setPos(topStationPoint + QPointF(0, stationLength * i));
        scene->addItem(stationNode);
        scene->addItem(new Edge(stationNode, centerNode));
        stationNodeList << stationNode;

        int receiverCount = station->getReceivers().size();
        QPointF topReceiverPoint(-400, stationNode->pos().y() - receiverLength / 2 * (receiverCount - 1));
        for (int j = 0; j < receiverCount; j++) {
            Receiver* receiver = station->getReceivers().at(j);
            ReceiverNode* receiverNode = new ReceiverNode(receiver, receiverLength * 0.8);
            receiverNode->setPos(topReceiverPoint + QPointF(0, receiverLength * j));
            scene->addItem(receiverNode);
            scene->addItem(new Edge(receiverNode, stationNode));
            receiverNodeList << receiverNode;
        }
    }

    int centerCount = otherCenterList.size();
    if (0 == centerCount) {
        return;
    }
    qreal centerLength = 400 / centerCount;

    QPointF topCenterPoint(400, - centerLength / 2 * (centerCount - 1));
    for (int i = 0; i < centerCount; i++) {
        OtherCenter* center = otherCenterList[i];
        CenterNode* otherCenterNode = new CenterNode(60, center->getCenterName());
        otherCenterNode->setPos(topCenterPoint + QPointF(0, centerLength * i));
        otherCenterNode->setStatus(1);
        scene->addItem(otherCenterNode);
        scene->addItem(new Edge(centerNode, otherCenterNode));
        centerNodeList << centerNode;
    }
}

void MainMonitorWidget::updateBJView()
{

}
