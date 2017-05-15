#include <QtGlobal>
#include <QGraphicsView>
#include <QCloseEvent>
#include <QDebug>

#include "mainmonitor_widget.h"
#include "ui_mainmonitor_widget.h"

#include "common.h"
#include "graphicsitem/edge.h"
#include "bean/center/main_center.h"

extern DeploymentType::Value deploymentType;
extern void* receiverStateSharedBufferPointer;
extern void* iGMASStateSharedBufferPointer;
extern void* otherCenterStateSharedBufferPointer;

MainMonitorWidget::MainMonitorWidget(SMAMTreeWidget* treeWidget, QWidget* parent) :
    QTabWidget(parent),
    ui(new Ui::MainMonitorWidget),
    standardStationList(treeWidget->getStandardStationList()),
    iGMASStationList(treeWidget->getIGMASStationList()),
    otherCenterList(treeWidget->getOtherCenterList()),
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
        case DeploymentType::XJ_DMZ:
            updateDMZView();
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
                         RECEIVER_STATE_SHAREDBUFFER_MAXITEMCOUNT * sizeof(ReceiverState));
                for (int i = 0; i < receiverNodeList.size(); i++) {
                    bool isConnected = false;
                    for (quint32 j = 0; j < RECEIVER_STATE_SHAREDBUFFER_MAXITEMCOUNT; j++) {
                        if (receiverState[j].isConnected && qstrcmp(receiverNodeList[i]->getReceiverMount().toStdString().c_str(), receiverState[j].mount) == 0) {
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
                iGMASStateSharedBuffer->readData((void*) iGMASState);
                for (int i = 0; i < iGMASStationList.size(); i++) {
                    for (quint32 j = 0; j < iGMASStateSharedBuffer->getItemCount(); j++) {
                        if (qstrcmp(iGMASNodeList[i]->getStationIPAddress().toStdString().c_str(), iGMASState[j].ipAddress) == 0)
                            iGMASNodeList[i]->setStatus(iGMASState[j].isConnected ? 1 : 2);
                    }
                }
            }
            break;
        case DeploymentType::XJ_DMZ:
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
        for (int i = 0; i < otherCenterList.size(); i++) {
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

    MainCenter* mainCenter = new MainCenter();
    mainCenter->setCenterName(tr("新疆中心"));
    CenterNode* mainCenterNode = new CenterNode(mainCenter, 50);
    mainCenterNode->setPos(0, 0);
    scene->addItem(mainCenterNode);

    DMZNode* dmzNode = new DMZNode(45);
    dmzNode->setPos(0, -150);
    scene->addItem(dmzNode);
    scene->addItem(new Edge(mainCenterNode, dmzNode));

    UsersNode* usersNode = new UsersNode(45);
    usersNode->setPos(150, -150);
    scene->addItem(usersNode);
    scene->addItem(new Edge(dmzNode, usersNode));

    FileNode* fileNode = new FileNode(40);
    fileNode->setPos(0, 150);
    scene->addItem(fileNode);
    scene->addItem((new Edge(mainCenterNode, fileNode))->setStatus(1));

//    HardDriveNode* hardDriveNode = new HardDriveNode(30);
//    hardDriveNode->setPos(150, 150);
//    scene->addItem(hardDriveNode);
//    scene->addItem(new Edge(fileNode, hardDriveNode));

    int stationCount = standardStationList.size();
    if (0 == stationCount) {
        return;
    }
    qreal stationLength = qMin((double) 400 / stationCount, 100.0);

    QPointF topStationPoint(-200, - stationLength / 2 * (stationCount - 1));
    for (int i = 0; i < stationCount; i++) {
        StandardStation* station = standardStationList[i];
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

    int centerCount = otherCenterList.size();
    if (0 == centerCount) {
        return;
    }
    qreal centerLength = 400 / centerCount;

    QPointF topCenterPoint(300, - centerLength / 2 * (centerCount - 1));
    for (int i = 0; i < centerCount; i++) {
        OtherCenter* center = otherCenterList[i];
        CenterNode* otherCenterNode = new CenterNode(center, 50);
        otherCenterNode->setPos(topCenterPoint + QPointF(0, centerLength * i));
        scene->addItem(otherCenterNode);
        scene->addItem(new Edge(mainCenterNode, otherCenterNode));
        otherCenterNodeList << otherCenterNode;
    }
}

void MainMonitorWidget::updateDMZView()
{
    scene->clear();

    DMZNode* dmzNode = new DMZNode(50);
    dmzNode->setPos(0, 0);
    scene->addItem(dmzNode);

    MainCenter* mainCenter = new MainCenter();
    mainCenter->setCenterName(tr("新疆中心"));
    CenterNode* mainCenterNode = new CenterNode(mainCenter, 50);
    mainCenterNode->setPos(-200, 0);
    scene->addItem(mainCenterNode);
    scene->addItem(new Edge(dmzNode, mainCenterNode));

    UsersNode* usersNode = new UsersNode(50);
    usersNode->setPos(200, 0);
    scene->addItem(usersNode);
    scene->addItem(new Edge(dmzNode, usersNode));
}

void MainMonitorWidget::updateBJView()
{
    scene->clear();
    iGMASNodeList.clear();
    otherCenterNodeList.clear();

    MainCenter* mainCenter = new MainCenter();
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

    int stationCount = iGMASStationList.size();
    if (0 == stationCount) {
        return;
    }
    qreal stationLength = qMin((double) 420 / ((stationCount > 10) ? 10 : stationCount), 100.0);

    QPointF lineOneTopStationPoint(-300, - stationLength / 2 * (((stationCount > 10) ? 10 : stationCount) - 1));
    QPointF lineTwoTopStationPoint(-350, - stationLength / 2 * (((stationCount > 10) ? 10 : stationCount) - 1));
    for (int i = 0; i < stationCount; i++) {
        IGMASStation* station = iGMASStationList[i];
        IGMASNode* stationNode = new IGMASNode(station, stationLength * 0.5);
        stationNode->setPos(((i > 9) ? lineTwoTopStationPoint : lineOneTopStationPoint) + QPointF(0, stationLength * (i % 10)));
        scene->addItem(stationNode);
        if (i < 10) {
            scene->addItem(new Edge(stationNode, mainCenterNode));
        }
        iGMASNodeList << stationNode;
    }

    int centerCount = otherCenterList.size();
    if (0 == centerCount) {
        return;
    }
    qreal centerLength = 400 / centerCount;

    QPointF topCenterPoint(300, - centerLength / 2 * (centerCount - 1));
    for (int i = 0; i < centerCount; i++) {
        OtherCenter* center = otherCenterList[i];
        CenterNode* otherCenterNode = new CenterNode(center, 50);
        otherCenterNode->setPos(topCenterPoint + QPointF(0, centerLength * i));
        scene->addItem(otherCenterNode);
        scene->addItem(new Edge(mainCenterNode, otherCenterNode));
        otherCenterNodeList << otherCenterNode;
    }
}
