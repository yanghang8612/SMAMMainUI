#include "systemmonitor_widget.h"
#include "ui_systemmonitor_widget.h"
#include "graphicsitem/receivernode.h"
#include "graphicsitem/stationnode.h"
#include "graphicsitem/centernode.h"
#include "graphicsitem/edge.h"

SystemMonitorWidget::SystemMonitorWidget(QWidget *parent, SMAMTreeWidget* treeWidget) :
	QWidget(parent),
	ui(new Ui::SystemMonitorWidget), treeWidget(treeWidget)
{
	ui->setupUi(this);
	scene = new QGraphicsScene(this);
    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-630, -350, 1260, 1000);
    ui->monitorView->resize(1260, 1000);
	ui->monitorView->setScene(scene);
	ui->monitorView->setCacheMode(QGraphicsView::CacheBackground);
	ui->monitorView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	ui->monitorView->setRenderHint(QPainter::Antialiasing);
	ui->monitorView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    updateView();
}

SystemMonitorWidget::~SystemMonitorWidget()
{
    delete ui;
}

void SystemMonitorWidget::updateView()
{
	CentreNode* centreNode = new CentreNode();
	centreNode->setPos(400, 0);
	scene->addItem(centreNode);

	int stationCount = treeWidget->standardStationList.size();
	QPointF topStationPoint(0, -100 * (stationCount - 1));
	for (int i = 0; i < stationCount; i++) {
		StandardStation* station = treeWidget->standardStationList.at(i);
		StationNode* stationNode = new StationNode(station);
		stationNode->setPos(topStationPoint + QPointF(0, 200 * i));
        stationNode->setStatus(1);
		scene->addItem(stationNode);
		scene->addItem(new Edge(stationNode, centreNode));

		int receiverCount = station->getReceivers().size();
        QPointF topReceiverPoint(-400, stationNode->pos().y() - 50 * (receiverCount - 1) - 1);
		for (int j = 0; j < receiverCount; j++) {
			Receiver* receiver = station->getReceivers().at(j);
			ReceiverNode* receiverNode = new ReceiverNode(receiver);
            receiverNode->setPos(topReceiverPoint + QPointF(0, 100 * j));
            receiverNode->setStatus(1);
			scene->addItem(receiverNode);
			scene->addItem(new Edge(receiverNode, stationNode));
		}
	}
}
