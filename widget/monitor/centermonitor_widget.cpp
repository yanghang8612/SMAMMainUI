#include <QtGlobal>
#include <QGraphicsView>
#include <QCloseEvent>
#include <QDebug>

#include "centermonitor_widget.h"
#include "ui_centermonitor_widget.h"

#include "common.h"
#include "item/edge.h"
#include "item/filenode.h"
#include "item/networknode.h"
#include "bean/main_center.h"
#include "utilities/config_helper.h"

CenterMonitorWidget::CenterMonitorWidget(QWidget* parent) :
    QTabWidget(parent),
    ui(new Ui::CenterMonitorWidget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-490, -205, 980, 410);
    //ui->monitorView->resize(996, 444);
    ui->monitorView->setScene(scene);
    ui->monitorView->setCacheMode(QGraphicsView::CacheBackground);
    ui->monitorView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    ui->monitorView->setRenderHint(QPainter::Antialiasing);

    initView();
    hide();
}

CenterMonitorWidget::~CenterMonitorWidget()
{
    delete ui;
}

void CenterMonitorWidget::updateView() {
    if (ConfigHelper::otherCenters.size() > otherCenterNodeList.size()) {
        int index = ConfigHelper::otherCenters.size() - 1;
        OtherCenterNode* otherCenterNode = new OtherCenterNode(ConfigHelper::otherCenters[index], 50, this);
        scene->addItem(otherCenterNode);
        otherCenterNodeList << otherCenterNode;
        TerminalNode* terminalNode = new TerminalNode(50);
        scene->addItem(terminalNode);
        terminalNodeList << terminalNode;
    }
    if (ConfigHelper::otherCenters.size() < otherCenterNodeList.size()) {
        for (int i = 0; i < otherCenterNodeList.size(); i++) {
            if (otherCenterNodeList[i]->getCenter()->getCenterID() == 0) {
                otherCenterNodeList[i]->clearEdge();
                scene->removeItem(otherCenterNodeList[i]);
                delete otherCenterNodeList[i];
                otherCenterNodeList.removeAt(i);
                scene->removeItem(terminalNodeList[i]);
                delete terminalNodeList[i];
                terminalNodeList.removeAt(i);
            }
        }
    }
    updateOtherCenterNodeList();
    scene->update();
}

void CenterMonitorWidget::initView()
{
    mainCenterNode = new MainCenterNode(new MainCenter(tr("北京中心")), 50);
    mainCenterNode->setPos(-150, 0);
    scene->addItem(mainCenterNode);

    NetworkNode* networkNode = new NetworkNode(50);
    networkNode->setPos(-350, 0);
    scene->addItem(networkNode);
    scene->addItem(new Edge(mainCenterNode, networkNode));

    FileNode* fileNode = new FileNode(40);
    fileNode->setPos(-150, 100);
    scene->addItem(fileNode);
    scene->addItem(new Edge(mainCenterNode, fileNode));

    for (int i = 0; i < ConfigHelper::otherCenters.size(); i++) {
        OtherCenterNode* otherCenterNode = new OtherCenterNode(ConfigHelper::otherCenters[i], 50, this);
        scene->addItem(otherCenterNode);
        otherCenterNodeList << otherCenterNode;
        TerminalNode* terminalNode = new TerminalNode(50);
        scene->addItem(terminalNode);
        terminalNodeList << terminalNode;
    }
    updateOtherCenterNodeList();
}

void CenterMonitorWidget::updateOtherCenterNodeList()
{
    qreal centerLength = 80;
    QPointF topCenterPoint(100, - centerLength / 2 * (ConfigHelper::otherCenters.size() - 1));
    for (int i = 0; i < otherCenterNodeList.size(); i++) {
        otherCenterNodeList[i]->setPos(topCenterPoint + QPointF(0, centerLength * i));
        otherCenterNodeList[i]->updateStateNode();
        otherCenterNodeList[i]->clearEdge();
        scene->addItem(new Edge(mainCenterNode, otherCenterNodeList[i]));
        terminalNodeList[i]->setPos(topCenterPoint + QPointF(200, centerLength * i));
        scene->addItem(new Edge(otherCenterNodeList[i], terminalNodeList[i]));
    }
}
