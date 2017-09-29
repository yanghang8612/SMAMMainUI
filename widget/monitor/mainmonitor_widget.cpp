#include <QtGlobal>
#include <QGraphicsView>
#include <QCloseEvent>
#include <QDebug>

#include "mainmonitor_widget.h"
#include "ui_mainmonitor_widget.h"

#include "common.h"
#include "item/edge.h"
#include "bean/main_center.h"
#include "utilities/config_helper.h"

extern DeploymentType::Value deploymentType;
extern void* receiverStateSharedBufferPointer;
extern void* iGMASStateSharedBufferPointer;
extern void* otherCenterStateSharedBufferPointer;

MainMonitorWidget::MainMonitorWidget(QWidget* parent) :
    QTabWidget(parent),
    ui(new Ui::MainMonitorWidget),
    receiverStateSharedBuffer(0), iGMASStateSharedBuffer(0), otherCenterStateSharedBuffer(0)
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

    deviceConnectStateCheckTimer = new QTimer(this);
    connect(deviceConnectStateCheckTimer, SIGNAL(timeout()), this, SLOT(updateDeviceConnectState()));
    deviceConnectStateCheckTimer->start(DEVICE_CONNECT_STATE_CHECK_TIMEINTERVAL);

    deviceTransferStateCheckTimer = new QTimer(this);
    connect(deviceTransferStateCheckTimer, SIGNAL(timeout()), this, SLOT(updateDeviceTransferState()));
    deviceTransferStateCheckTimer->start(DEVICE_TRANSFER_STATE_CHECK_TIMEINTERVAL);
}

MainMonitorWidget::~MainMonitorWidget()
{
    delete ui;
}

void MainMonitorWidget::updateView() {
    qDebug() << "SMAMMainUI:" << "Update view is invoked.";
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

void MainMonitorWidget::updateDeviceConnectState()
{
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            if (receiverStateSharedBuffer == 0) {
                receiverStateSharedBuffer = (receiverStateSharedBufferPointer == 0) ? 0 : new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                                                                                           SharedBuffer::ONLY_READ,
                                                                                                           receiverStateSharedBufferPointer,
                                                                                                           sizeof(ReceiverState));
            }
            else {
                qMemCopy(receiverState,
                         (char*) receiverStateSharedBufferPointer + 4,
                         RECEIVER_MAXITEMCOUNT * sizeof(ReceiverState));
                for (int i = 0; i < receiverNodeList.size(); i++) {
                    bool isConnected = false;
                    for (quint32 j = 0; j < RECEIVER_MAXITEMCOUNT; j++) {
                        if (receiverState[j].isConnected && qstrcmp(receiverNodeList[i]->getReceiverMount().toStdString().c_str(), receiverState[j].mount + 1) == 0) {
                            isConnected = true;
                            break;
                        }
                    }
                    receiverNodeList[i]->setStatus(isConnected ? 1 : 2);
                }
            }
            break;
        case DeploymentType::BJ_CENTER:
            if (iGMASStateSharedBuffer == 0) {
                iGMASStateSharedBuffer = (iGMASStateSharedBufferPointer == 0) ? 0 : new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                                                                                     SharedBuffer::ONLY_READ,
                                                                                                     iGMASStateSharedBufferPointer,
                                                                                                     sizeof(IGMASState));
            }
            else {
                qMemCopy(iGMASState,
                         (char*) iGMASStateSharedBufferPointer + 4,
                         IGMASSTATION_MAXITEMCOUNT * sizeof(IGMASState));
                for (int i = 0; i < iGMASNodeList.size(); i++) {
                    bool isConnected = false;
                    for (quint32 j = 0; j < IGMASSTATION_MAXITEMCOUNT; j++) {
                        if (iGMASState[j].isConnected && qstrcmp(iGMASNodeList[i]->getStationIPAddress().toStdString().c_str(), iGMASState[j].ipAddress) == 0) {
                            isConnected = true;
                            break;
                        }

                    }
                    iGMASNodeList[i]->setStatus(isConnected ? 1 : 2);
                }
            }
            break;
    }
    if (otherCenterStateSharedBuffer == 0) {
        otherCenterStateSharedBuffer = (otherCenterStateSharedBufferPointer == 0) ? 0 : new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                                                                                         SharedBuffer::ONLY_READ,
                                                                                                         otherCenterStateSharedBufferPointer,
                                                                                                         sizeof(OtherCenterState));
    }
    else {
        otherCenterStateSharedBuffer->readData((void*) otherCenterState);
        for (int i = 0; i < ConfigHelper::otherCenters.size(); i++) {
            for (quint32 j = 0; j < otherCenterStateSharedBuffer->getItemCount(); j++) {
                if (qstrcmp(otherCenterNodeList[i]->getCenterIPAddress().toStdString().c_str(), otherCenterState[j].ipAddress) == 0)
                    otherCenterNodeList[i]->setStatus(otherCenterState[j].isConnected ? 1 : 2);
            }
        }
    }
}

void MainMonitorWidget::updateDeviceTransferState()
{

}

void MainMonitorWidget::updateXJView()
{
    scene->clear();
    receiverNodeList.clear();
    otherCenterNodeList.clear();

    OtherCenter* mainCenter = new OtherCenter();
    mainCenter->setCenterName(tr("新疆中心"));
    CenterNode* mainCenterNode = new CenterNode(mainCenter, 50);
    mainCenterNode->setPos(0, 0);
    scene->addItem(mainCenterNode);

    UsersNode* usersNode = new UsersNode(45);
    usersNode->setPos(0, -150);
    scene->addItem(usersNode);
    scene->addItem(new Edge(mainCenterNode, usersNode));

    FileNode* fileNode = new FileNode(40);
    fileNode->setPos(0, 150);
    scene->addItem(fileNode);
    scene->addItem((new Edge(mainCenterNode, fileNode))->setStatus(1));

//    HardDriveNode* hardDriveNode = new HardDriveNode(30);
//    hardDriveNode->setPos(150, 150);
//    scene->addItem(hardDriveNode);
//    scene->addItem(new Edge(fileNode, hardDriveNode));

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

    int centerCount = ConfigHelper::otherCenters.size();
    if (0 == centerCount) {
        return;
    }
    qreal centerLength = 400 / centerCount;

    QPointF topCenterPoint(300, - centerLength / 2 * (centerCount - 1));
    for (int i = 0; i < centerCount; i++) {
        OtherCenter* center = ConfigHelper::otherCenters[i];
        CenterNode* otherCenterNode = new CenterNode(center, 50);
        otherCenterNode->setPos(topCenterPoint + QPointF(0, centerLength * i));
        scene->addItem(otherCenterNode);
        scene->addItem(new Edge(mainCenterNode, otherCenterNode));
        otherCenterNodeList << otherCenterNode;
    }
}

void MainMonitorWidget::updateBJView()
{
    scene->clear();
    iGMASNodeList.clear();
    otherCenterNodeList.clear();

    OtherCenter* mainCenter = new OtherCenter();
    mainCenter->setCenterName(tr("北京中心"));
    CenterNode* mainCenterNode = new CenterNode(mainCenter, 50);
    mainCenterNode->setPos(0, 0);
    scene->addItem(mainCenterNode);

    UsersNode* usersNode = new UsersNode(45);
    usersNode->setPos(0, -150);
    scene->addItem(usersNode);
    scene->addItem(new Edge(mainCenterNode, usersNode));

    FileNode* fileNode = new FileNode(40);
    fileNode->setPos(0, 150);
    scene->addItem(fileNode);
    scene->addItem((new Edge(mainCenterNode, fileNode))->setStatus(1));

//    HardDriveNode* hardDriveNode = new HardDriveNode(30);
//    hardDriveNode->setPos(150, 150);
//    scene->addItem(hardDriveNode);
//    scene->addItem(new Edge(fileNode, hardDriveNode));

    int stationCount = ConfigHelper::iGMASStations.size();
    if (0 == stationCount) {
        return;
    }
    qreal stationLength = qMin((double) 420 / ((stationCount > 6) ? 6 : stationCount), 100.0);

    QPointF startStationPoint(-450, - stationLength / 2 * (((stationCount > 6) ? 6 : stationCount) - 1));
    for (int i = 0; i < stationCount; i++) {
        iGMASStation* station = ConfigHelper::iGMASStations[i];
        iGMASNode* stationNode = new iGMASNode(station, stationLength * 0.5, this);
        stationNode->setPos(startStationPoint + QPointF((i / 6) * stationLength + 10, stationLength * (i % 6)));
        scene->addItem(stationNode);
        iGMASNodeList << stationNode;
    }

    int centerCount = ConfigHelper::otherCenters.size();
    if (0 == centerCount) {
        return;
    }
    qreal centerLength = 400 / centerCount;

    QPointF topCenterPoint(300, - centerLength / 2 * (centerCount - 1));
    for (int i = 0; i < centerCount; i++) {
        OtherCenter* center = ConfigHelper::otherCenters[i];
        CenterNode* otherCenterNode = new CenterNode(center, 50);
        otherCenterNode->setPos(topCenterPoint + QPointF(0, centerLength * i));
        scene->addItem(otherCenterNode);
        scene->addItem(new Edge(mainCenterNode, otherCenterNode));
        otherCenterNodeList << otherCenterNode;
    }
}
