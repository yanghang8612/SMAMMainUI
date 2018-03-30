#include <QGraphicsScene>
#include <QMessageBox>
#include <QMenu>
#include <QFile>
#include <QDebug>

#include "smam_treewidget.h"
#include "common_treeitem.h"
#include "monitor_treeitem.h"
#include "main_component_header.h"

#include "widget/dialog/datacenter_edit_dialog.h"
#include "widget/dialog/monitorstation_edit_dialog.h"
#include "widget/dialog/othercenter_edit_dialog.h"
#include "widget/dialog/receiver_edit_dialog.h"
#include "widget/dialog/standardstation_edit_dialog.h"

#define STANDARDROOT_TREEITEM_TYPE 00
#define STANDARDNODE_TREEITEM_TYPE 01
#define RECEIVER_TREEITEM_TYPE 02

#define MONITORSTATIONROOT_TREEITEM_TYPE 10
#define MONITORSTATIONNODE_TREEITEM_TYPE 11

#define DATACENTERROOT_TREEITEM_TYPE 20
#define DATACENTERNODE_TREEITEM_TYPE 21

#define CENTERROOT_TREEITEM_TYPE 30
#define CENTERNODE_TREEITEM_TYPE 31

#define MEMINFO_TREEITEM_TYPE 40

extern DeploymentType::Value deploymentType;

SMAMTreeWidget::SMAMTreeWidget(QTreeWidget* tree, QVBoxLayout* container) :
    tree(tree), container(container),
    currentContentWidget(0)
{
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            initAtXJ();
            break;
        case DeploymentType::BJ_CENTER:
            initAtBJ();
            break;
        default:
            qDebug() << "SMAMMainUI:" << "No match deploymenttype";
            break;
    }
    connect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenu(QPoint)));
    connect(tree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(handleItemClicked(QTreeWidgetItem*)));

    registerSignalSender(this);
}

SMAMTreeWidget::~SMAMTreeWidget()
{
    removeSignalSender(this);
}

void SMAMTreeWidget::showRightMenu(QPoint pos)
{
	QTreeWidgetItem* curItem = tree->itemAt(pos);
    if (curItem == NULL) {
		return;
    }

	QMenu* popMenu =new QMenu;
    switch (curItem->type()) {
        case STANDARDROOT_TREEITEM_TYPE:
        {
            QAction* addNewStandardStation = new QAction(QIcon(":/add"), tr("添加基准站"), this);
            connect(addNewStandardStation, SIGNAL(triggered(bool)), this, SLOT(showAddNewStandardStationDialog()));
            popMenu->addAction(addNewStandardStation);
            break;
        }
        case STANDARDNODE_TREEITEM_TYPE:
        {
            QAction* addNewReceiver = new QAction(QIcon(":/add"), tr("添加接收机"), this);
            connect(addNewReceiver, SIGNAL(triggered(bool)), this, SLOT(showAddNewReceiverDialog()));
            popMenu->addAction(addNewReceiver);
            QAction* modifyStandardStation = new QAction(QIcon(":/modify"), tr("编辑基准站"), this);
            connect(modifyStandardStation, SIGNAL(triggered(bool)), this, SLOT(showModifyStandardStationDialog()));
            popMenu->addAction(modifyStandardStation);
            QAction* deleteStandardStation = new QAction(QIcon(":/delete"), tr("删除基准站"), this);
            connect(deleteStandardStation, SIGNAL(triggered(bool)), this, SLOT(deleteStandardStation()));
            popMenu->addAction(deleteStandardStation);
            break;
        }
        case RECEIVER_TREEITEM_TYPE:
        {
//            QAction* startReceiver = new QAction(tr("启动接收机"), this);
//            popMenu->addAction(startReceiver);
//            QAction* stopReceiver = new QAction(tr("停止接收机"), this);
//            popMenu->addAction(stopReceiver);
            QAction* modifyReceiver = new QAction(QIcon(":/modify"), tr("编辑接收机"), this);
            connect(modifyReceiver, SIGNAL(triggered(bool)), this, SLOT(showModifyReceiverDialog()));
            popMenu->addAction(modifyReceiver);
            QAction* deleteReceiver = new QAction(QIcon(":/delete"), tr("删除接收机"), this);
            connect(deleteReceiver, SIGNAL(triggered(bool)), this, SLOT(deleteReceiver()));
            popMenu->addAction(deleteReceiver);
            break;
        }
        case MONITORSTATIONROOT_TREEITEM_TYPE:
        {
            QAction* addNewMonitorStation = new QAction(QIcon(":/add"), tr("添加监测站"), this);
            connect(addNewMonitorStation, SIGNAL(triggered(bool)), this, SLOT(showAddNewMonitorStationDialog()));
            popMenu->addAction(addNewMonitorStation);
            break;
        }
        case MONITORSTATIONNODE_TREEITEM_TYPE:
        {
            int index = tree->currentIndex().row();
            if (ConfigHelper::monitorStations[index]->getIsAvailable()) {
                QAction* stopMonitorStation = new QAction(QIcon(":/stop"), tr("停止监测站"), this);
                connect(stopMonitorStation, SIGNAL(triggered(bool)), this, SLOT(stopMonitorStation()));
                popMenu->addAction(stopMonitorStation);
            }
            else {
                QAction* startMonitorStation = new QAction(QIcon(":/start"), tr("启动监测站"), this);
                connect(startMonitorStation, SIGNAL(triggered(bool)), this, SLOT(startMonitorStation()));
                popMenu->addAction(startMonitorStation);
            }
            QAction* modifyMonitorStation = new QAction(QIcon(":/modify"), tr("编辑监测站"), this);
            connect(modifyMonitorStation, SIGNAL(triggered(bool)), this, SLOT(showModifyMonitorStationDialog()));
            popMenu->addAction(modifyMonitorStation);
            QAction* deleteMonitorStation = new QAction(QIcon(":/delete"), tr("删除监测站"), this);
            connect(deleteMonitorStation, SIGNAL(triggered(bool)), this, SLOT(deleteMonitorStation()));
            popMenu->addAction(deleteMonitorStation);
            break;
        }
        case DATACENTERROOT_TREEITEM_TYPE:
        {
            QAction* addNewDataCenter = new QAction(QIcon(":/add"), tr("添加数据中心"), this);
            connect(addNewDataCenter, SIGNAL(triggered(bool)), this, SLOT(showAddNewDataCenterDialog()));
            popMenu->addAction(addNewDataCenter);
            break;
        }
        case DATACENTERNODE_TREEITEM_TYPE:
        {
            QAction* modifyDataCenter = new QAction(QIcon(":/modify"), tr("编辑数据中心"), this);
            connect(modifyDataCenter, SIGNAL(triggered(bool)), this, SLOT(showModifyDataCenterDialog()));
            popMenu->addAction(modifyDataCenter);
            QAction* deleteDataCenter = new QAction(QIcon(":/delete"), tr("删除数据中心"), this);
            connect(deleteDataCenter, SIGNAL(triggered(bool)), this, SLOT(deleteDataCenter()));
            popMenu->addAction(deleteDataCenter);
            break;
        }
        case CENTERROOT_TREEITEM_TYPE:
        {
            QAction* addNewCenter = new QAction(QIcon(":/add"), tr("添加数据中心"), this);
            connect(addNewCenter, SIGNAL(triggered(bool)), this, SLOT(showAddNewOtherCenterDialog()));
            popMenu->addAction(addNewCenter);
            break;
        }
        case CENTERNODE_TREEITEM_TYPE:
        {
            QAction* modifyCenter = new QAction(QIcon(":/modify"), tr("编辑数据中心"), this);
            connect(modifyCenter, SIGNAL(triggered(bool)), this, SLOT(showModifyOtherCenterDialog()));
            popMenu->addAction(modifyCenter);
            QAction* deleteCenter = new QAction(QIcon(":/delete"), tr("删除数据中心"), this);
            connect(deleteCenter, SIGNAL(triggered(bool)), this, SLOT(deleteOtherCenter()));
            popMenu->addAction(deleteCenter);
            break;
        }
    }
	popMenu->exec(QCursor::pos());
}

void SMAMTreeWidget::handleItemClicked(QTreeWidgetItem* item)
{
    currentContentWidget->hide();
    int index = tree->currentIndex().row(), parentIndex;
    QWidget* preContentWidget = currentContentWidget;
    switch (item->type()) {
        case STANDARDROOT_TREEITEM_TYPE:
            currentContentWidget = receiverMonitorWidget;
            break;
        case MONITORSTATIONROOT_TREEITEM_TYPE:
        case DATACENTERROOT_TREEITEM_TYPE:
            currentContentWidget = stationMonitorWidget;
            break;
        case CENTERROOT_TREEITEM_TYPE:
            currentContentWidget = centerMonitorWidget;
            break;
        case MEMINFO_TREEITEM_TYPE:
            currentContentWidget = sharedMemoryInfoWidget;
            break;
        case STANDARDNODE_TREEITEM_TYPE:
            standardStationInfoWidget->setStation(ConfigHelper::standardStations[index]);
            currentContentWidget = standardStationInfoWidget;
            break;
        case RECEIVER_TREEITEM_TYPE:
            parentIndex = standardStationTreeRoot->indexOfChild(tree->currentItem()->parent());
            receiverInfoWidget->setReceiver(ConfigHelper::standardStations[parentIndex]->getReceivers()[index]);
            currentContentWidget = receiverInfoWidget;
            break;
        case MONITORSTATIONNODE_TREEITEM_TYPE:
            monitorStationInfoWidget->setStation(ConfigHelper::monitorStations[index]);
            currentContentWidget = monitorStationInfoWidget;
            break;
        case DATACENTERNODE_TREEITEM_TYPE:
            dataCenterWidget->setDataCenter(ConfigHelper::dataCenters[index]);
            currentContentWidget = dataCenterWidget;
            break;
        case CENTERNODE_TREEITEM_TYPE:
            centerInfoWidget->setCenter(ConfigHelper::otherCenters[index]);
            currentContentWidget = centerInfoWidget;
            break;
        default:
            return;
    }
    if (preContentWidget != currentContentWidget) {
        preContentWidget->hide();
    }
    currentContentWidget->show();
}

void SMAMTreeWidget::showAddNewStandardStationDialog()
{
    StandardStationEditDialog* dialog = new StandardStationEditDialog(tree);
	connect(dialog, SIGNAL(confirmButtonClicked(StandardStation*)), this, SLOT(addNewStandardStation(StandardStation*)));
	dialog->show();
}

void SMAMTreeWidget::addNewStandardStation(StandardStation* station)
{
    ConfigHelper::standardStations << station;
    ConfigHelper::update();
    centerMonitorWidget->updateView();
    tree->currentItem()->addChild(new CommonTreeItem(STANDARDNODE_TREEITEM_TYPE, station->getStationName(), ":/standard_station"));
}

void SMAMTreeWidget::showModifyStandardStationDialog()
{
    int index = tree->currentIndex().row();
    StandardStationEditDialog* dialog = new StandardStationEditDialog(ConfigHelper::standardStations[index], tree);
	connect(dialog, SIGNAL(confirmButtonClicked(StandardStation*)), this, SLOT(modifyStandardStation(StandardStation*)));
	dialog->show();
}

void SMAMTreeWidget::modifyStandardStation(StandardStation* station)
{
    handleItemClicked(tree->currentItem());
    ConfigHelper::update();
    centerMonitorWidget->updateView();
    tree->currentItem()->setText(0, station->getStationName());
}

void SMAMTreeWidget::deleteStandardStation()
{
    int index = tree->currentIndex().row();
    StandardStation* station = ConfigHelper::standardStations[index];
    QString content = tr("确认删除基准站<") + station->getStationName() + tr(">吗？");
    QMessageBox box(QMessageBox::Warning, tr("提示"), content);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::No , tr("取消"));
    box.setButtonText(QMessageBox::Yes , tr("确认"));
    if (box.exec() == QMessageBox::Yes) {
        ConfigHelper::standardStations.removeAt(index);
        ConfigHelper::update();
        centerMonitorWidget->updateView();
        delete tree->currentItem()->parent()->takeChild(index);
	}
}

void SMAMTreeWidget::showAddNewReceiverDialog()
{
    int index = tree->currentIndex().row();
    if (ConfigHelper::standardStations[index]->getReceivers().size() >= MAX_RECEIVER_COUNT_PERSTATION) {
        QMessageBox box(QMessageBox::Warning, tr("提示"), tr("超过最大单个基准站所能容纳接收机数目。"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok , tr("确认"));
        box.exec();
    }
    else {
        ReceiverEditDialog* dialog = new ReceiverEditDialog(tree);
        connect(dialog, SIGNAL(confirmButtonClicked(Receiver*)), this, SLOT(addNewReceiver(Receiver*)));
        dialog->show();
    }
}

void SMAMTreeWidget::addNewReceiver(Receiver* receiver)
{
    int index = tree->currentIndex().row();
    ConfigHelper::standardStations[index]->addReceiver(receiver);
    ConfigHelper::update();
    centerMonitorWidget->updateView();
    tree->currentItem()->addChild(new CommonTreeItem(RECEIVER_TREEITEM_TYPE, receiver->getReceiverName(), ":/standard_receiver"));
}

void SMAMTreeWidget::showModifyReceiverDialog()
{
    int index = tree->currentIndex().row();
    int parentIndex = standardStationTreeRoot->indexOfChild(tree->currentItem()->parent());
    ReceiverEditDialog* dialog = new ReceiverEditDialog(ConfigHelper::standardStations[parentIndex]->getReceivers()[index], tree);
	connect(dialog, SIGNAL(confirmButtonClicked(Receiver*)), this, SLOT(modifyReceiver(Receiver*)));
	dialog->show();
}

void SMAMTreeWidget::modifyReceiver(Receiver* receiver)
{
    ConfigHelper::update();
    centerMonitorWidget->updateView();
    tree->currentItem()->setText(0, receiver->getReceiverName());
}

void SMAMTreeWidget::deleteReceiver()
{
    int index = tree->currentIndex().row();
    int parentIndex = standardStationTreeRoot->indexOfChild(tree->currentItem()->parent());
    Receiver* receiver = ConfigHelper::standardStations[parentIndex]->getReceivers()[index];\
    QString content = tr("确认删除接受机<") + receiver->getReceiverName() + tr(">吗？");
    QMessageBox box(QMessageBox::Warning, tr("提示"), content);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::No , tr("取消"));
    box.setButtonText(QMessageBox::Yes , tr("确认"));
    if (box.exec() == QMessageBox::Yes) {
        ConfigHelper::clearReceiverMemID(receiver->getMemID());
        ConfigHelper::standardStations[parentIndex]->removerReceiver(index);
        ConfigHelper::update();
        centerMonitorWidget->updateView();
        delete tree->currentItem()->parent()->takeChild(index);
    }
}

void SMAMTreeWidget::showAddNewMonitorStationDialog()
{
    if (ConfigHelper::monitorStations.size() > MONITORSTATION_MAXITEMCOUNT) {
        QMessageBox box(QMessageBox::Warning, tr("提示"), tr("超过最大单个中心所能容纳的监测站数目。"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok , tr("确认"));
        box.exec();
    }
    else {
        MonitorStationEditDialog* dialog = new MonitorStationEditDialog(tree);
        connect(dialog, SIGNAL(confirmButtonClicked(MonitorStation*)), this, SLOT(addNewMonitorStation(MonitorStation*)));
        dialog->show();
    }
}

void SMAMTreeWidget::addNewMonitorStation(MonitorStation* station)
{
    tree->currentItem()->addChild(new MonitorTreeItem(MONITORSTATIONNODE_TREEITEM_TYPE, station));
    centerMonitorWidget->updateView();
    station->setMemID(ConfigHelper::findFreeMonitorStationMemID());
    ConfigHelper::monitorStations << station;
    ConfigHelper::update();
    emit iGMASStationAdded(station->getBufferItem());
}

void SMAMTreeWidget::startMonitorStation()
{
    tree->currentItem()->setIcon(0, QIcon(":/monitor_station_green"));
    int index = tree->currentIndex().row();
    MonitorStation* station = ConfigHelper::monitorStations[index];
    station->setIsAvailable(true);
    ConfigHelper::update();
    emit iGMASStationStarted(station->getMemID());
}

void SMAMTreeWidget::stopMonitorStation()
{
    tree->currentItem()->setIcon(0, QIcon(":/monitor_station"));
    int index = tree->currentIndex().row();
    MonitorStation* station = ConfigHelper::monitorStations[index];
    station->setIsAvailable(false);
    ConfigHelper::update();
    emit iGMASStationStoped(station->getMemID());
}

void SMAMTreeWidget::showModifyMonitorStationDialog()
{
    int index = tree->currentIndex().row();
    MonitorStationEditDialog* dialog = new MonitorStationEditDialog(ConfigHelper::monitorStations[index], tree);
    connect(dialog, SIGNAL(confirmButtonClicked(MonitorStation*)), this, SLOT(modifyMonitorStation(MonitorStation*)));
    dialog->show();
}

void SMAMTreeWidget::modifyMonitorStation(MonitorStation* station)
{
    handleItemClicked(tree->currentItem());
    ConfigHelper::update();
    stationMonitorWidget->updateView();
    tree->currentItem()->setText(0, station->getDescription());
    emit iGMASStationModified(station->getMemID());
}

void SMAMTreeWidget::deleteMonitorStation()
{
    int index = tree->currentIndex().row();
    MonitorStation* station = ConfigHelper::monitorStations[index];
    QString content = tr("确认删除监测站<") + station->getDescription() + tr(">吗？");
    QMessageBox box(QMessageBox::Warning, tr("提示"), content);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::No , tr("取消"));
    box.setButtonText(QMessageBox::Yes , tr("确认"));
    if (box.exec() == QMessageBox::Yes) {
        handleItemClicked(tree->currentItem()->parent());
        ConfigHelper::clearMonitorStationMemID(station->getMemID());
        ConfigHelper::monitorStations.removeAt(index);
        ConfigHelper::update();
        emit iGMASStationDeleted(station->getMemID());
        delete tree->currentItem()->parent()->takeChild(index);
        delete station;
        centerMonitorWidget->updateView();
    }
}

void SMAMTreeWidget::showAddNewDataCenterDialog()
{
    if (ConfigHelper::dataCenters.size() > DATACENTER_MAXITEMCOUNT) {
        QMessageBox box(QMessageBox::Warning, tr("提示"), tr("超过最大单个中心所能容纳的数据中心数目。"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok , tr("确认"));
        box.exec();
    }
    else {
        DataCenterEditDialog* dialog = new DataCenterEditDialog(tree);
        connect(dialog, SIGNAL(confirmButtonClicked(DataCenter*)), this, SLOT(addNewDataCenter(DataCenter*)));
        dialog->show();
    }
}

void SMAMTreeWidget::addNewDataCenter(DataCenter* dataCenter)
{
    dataCenter->setCenterID(ConfigHelper::getNewDataCenterID());
    ConfigHelper::dataCenters << dataCenter;
    ConfigHelper::update();
    tree->currentItem()->addChild(new CommonTreeItem(DATACENTERNODE_TREEITEM_TYPE, dataCenter->getCenterName(), ":/datacenter"));
    emit DataCenterAdded(dataCenter->getBufferItem());
}

void SMAMTreeWidget::showModifyDataCenterDialog()
{
    int index = tree->currentIndex().row();
    DataCenterEditDialog* dialog = new DataCenterEditDialog(ConfigHelper::dataCenters[index], tree);
    connect(dialog, SIGNAL(confirmButtonClicked(DataCenter*)), this, SLOT(modifyDataCenter(DataCenter*)));
    dialog->show();
}

void SMAMTreeWidget::modifyDataCenter(DataCenter* dataCenter)
{
    handleItemClicked(tree->currentItem());
    ConfigHelper::update();
    tree->currentItem()->setText(0, dataCenter->getCenterName());
    emit DataCenterModified(dataCenter->getCenterID());
}

void SMAMTreeWidget::deleteDataCenter()
{
    int index = tree->currentIndex().row();
    DataCenter* dataCenter = ConfigHelper::dataCenters[index];
    QString content = tr("移除数据中心将导致某些监测站断线重连！\n确认删除数据中心<") + dataCenter->getCenterName() + tr(">吗？");
    QMessageBox box(QMessageBox::Warning, tr("提示"), content);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::No , tr("取消"));
    box.setButtonText(QMessageBox::Yes , tr("确认"));
    if (box.exec() == QMessageBox::Yes) {
        handleItemClicked(tree->currentItem()->parent());
        ConfigHelper::dataCenters.removeAt(index);
        ConfigHelper::deleteDataCenter(dataCenter->getCenterID());
        ConfigHelper::update();
        emit DataCenterDeleted(dataCenter->getCenterID());
        delete tree->currentItem()->parent()->takeChild(index);
        delete dataCenter;
    }
}

void SMAMTreeWidget::showAddNewOtherCenterDialog()
{
    if (ConfigHelper::otherCenters.size() > OTHERCENTER_MAXITEMCOUNT) {
        QMessageBox box(QMessageBox::Warning, tr("提示"), tr("超过最大分中心数目。"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok , tr("确认"));
        box.exec();
    }
    else {
        OtherCenterEditDialog* dialog = new OtherCenterEditDialog(tree);
        connect(dialog, SIGNAL(confirmButtonClicked(OtherCenter*)), this, SLOT(addNewOtherCenter(OtherCenter*)));
        dialog->show();
    }
}

void SMAMTreeWidget::addNewOtherCenter(OtherCenter* center)
{
    center->setCenterID(ConfigHelper::getNewOtherCenterID());
    ConfigHelper::otherCenters << center;
    ConfigHelper::update();
    centerMonitorWidget->updateView();
    tree->currentItem()->addChild(new CommonTreeItem(CENTERNODE_TREEITEM_TYPE, center->getCenterName(), ":/other_center"));
    emit OtherCenterAdded(center->getBufferItem());
}

void SMAMTreeWidget::showModifyOtherCenterDialog()
{
    int index = tree->currentIndex().row();
    OtherCenterEditDialog* dialog = new OtherCenterEditDialog(ConfigHelper::otherCenters[index], tree);
    connect(dialog, SIGNAL(confirmButtonClicked(OtherCenter*)), this, SLOT(modifyOtherCenter(OtherCenter*)));
    dialog->show();
}

void SMAMTreeWidget::modifyOtherCenter(OtherCenter* center)
{
    handleItemClicked(tree->currentItem());
    ConfigHelper::update();
    centerMonitorWidget->updateView();
    tree->currentItem()->setText(0, center->getCenterName());
    emit OtherCenterModified(center->getCenterID());
}

void SMAMTreeWidget::deleteOtherCenter()
{
    int index = tree->currentIndex().row();
    OtherCenter* center = ConfigHelper::otherCenters[index];
    QString content = tr("确认删除分中心<") + center->getCenterName() + tr(">吗？");
    QMessageBox box(QMessageBox::Warning, "提示", content);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::No , tr("取消"));
    box.setButtonText(QMessageBox::Yes , tr("确认"));
    if (box.exec() == QMessageBox::Yes) {
        handleItemClicked(tree->currentItem()->parent());
        ConfigHelper::otherCenters.removeAt(index);
        ConfigHelper::update();
        emit OtherCenterDeleted(center->getCenterID());
        delete tree->currentItem()->parent()->takeChild(tree->currentIndex().row());
        delete center;
        centerMonitorWidget->updateView();
    }
}

void SMAMTreeWidget::initAtBJ()
{
    stationMonitorWidget = new StationMonitorWidget();
    centerMonitorWidget = new CenterMonitorWidget();
    monitorStationInfoWidget = new MonitorStationInfoWidget();
    dataCenterWidget = new DataCenterWidget();
    centerInfoWidget = new CenterInfoWidget();
    sharedMemoryInfoWidget = new SharedMemoryInfoWidget();
    container->addWidget(centerMonitorWidget);
    container->addWidget(stationMonitorWidget);
    container->addWidget(monitorStationInfoWidget);
    container->addWidget(dataCenterWidget);
    container->addWidget(centerInfoWidget);
    container->addWidget(sharedMemoryInfoWidget);
    currentContentWidget = stationMonitorWidget;

    monitorStationTreeRoot = new CommonTreeItem(MONITORSTATIONROOT_TREEITEM_TYPE, tr("全球监测站网"), ":/monitor_root");
    for (int i = 0; i < ConfigHelper::monitorStations.size(); i++) {
        MonitorStation* station = ConfigHelper::monitorStations[i];
        monitorStationTreeRoot->addChild(new MonitorTreeItem(MONITORSTATIONNODE_TREEITEM_TYPE, station));
    }

    dataCenterTreeRoot = new CommonTreeItem(DATACENTERROOT_TREEITEM_TYPE, tr("站网数据中心"), ":/data_root");
    for (int i = 0; i < ConfigHelper::dataCenters.size(); i++) {
        DataCenter* center = ConfigHelper::dataCenters[i];
        dataCenterTreeRoot->addChild(new CommonTreeItem(DATACENTERNODE_TREEITEM_TYPE, center->getCenterName(), ":/data_center"));
    }

    otherCenterTreeRoot = new CommonTreeItem(CENTERROOT_TREEITEM_TYPE, tr("播发服务分中心"), ":/center_root");
    for (int i = 0; i < ConfigHelper::otherCenters.size(); i++) {
        OtherCenter* center = ConfigHelper::otherCenters[i];
        otherCenterTreeRoot->addChild(new CommonTreeItem(CENTERNODE_TREEITEM_TYPE, center->getCenterName(), ":/other_center"));
    }

    //memoryTreeRoot = new CommonTreeItem(MEMINFO_TREEITEM_TYPE, tr("内存管理"), ":/2");

    tree->setColumnCount(1);
    tree->addTopLevelItem(monitorStationTreeRoot);
    tree->addTopLevelItem(dataCenterTreeRoot);
    tree->addTopLevelItem(otherCenterTreeRoot);
    //tree->addTopLevelItem(memoryTreeRoot);
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    monitorStationTreeRoot->setExpanded(true);
    dataCenterTreeRoot->setExpanded(true);
    otherCenterTreeRoot->setExpanded(true);
}

void SMAMTreeWidget::initAtXJ()
{
    receiverMonitorWidget = new ReceiverMonitorWidget();
    standardStationInfoWidget = new StandardStationInfoWidget();
    receiverInfoWidget = new ReceiverInfoWidget();
    sharedMemoryInfoWidget = new SharedMemoryInfoWidget();
    container->addWidget(receiverMonitorWidget);
    container->addWidget(standardStationInfoWidget);
    container->addWidget(receiverInfoWidget);
    container->addWidget(sharedMemoryInfoWidget);
    currentContentWidget = receiverMonitorWidget;

    standardStationTreeRoot = new CommonTreeItem(STANDARDROOT_TREEITEM_TYPE, tr("基准站管理"), ":/standard_root");
    for (int i = 0; i < ConfigHelper::standardStations.size(); i++) {
        StandardStation* station = ConfigHelper::standardStations[i];
        QTreeWidgetItem* stationTreeItem = new CommonTreeItem(STANDARDNODE_TREEITEM_TYPE, station->getStationName(), ":/standard_station");
        standardStationTreeRoot->addChild(stationTreeItem);
        for (int j = 0; j < station->getReceivers().size(); j++) {
            Receiver* receiver = station->getReceivers()[j];
            stationTreeItem->addChild(new CommonTreeItem(RECEIVER_TREEITEM_TYPE, receiver->getReceiverName(), ":/receiver"));
        }
    }

    otherCenterTreeRoot = new CommonTreeItem(CENTERROOT_TREEITEM_TYPE, tr("数据中心"), ":/center_root");
    for (int i = 0; i < ConfigHelper::otherCenters.size(); i++) {
        OtherCenter* center = ConfigHelper::otherCenters[i];
        otherCenterTreeRoot->addChild(new CommonTreeItem(CENTERNODE_TREEITEM_TYPE, center->getCenterName(), ":/other_center"));
    }

    memoryTreeRoot = new CommonTreeItem(MEMINFO_TREEITEM_TYPE, tr("内存管理"), ":/2");

	tree->setColumnCount(1);
    tree->addTopLevelItem(standardStationTreeRoot);
    tree->addTopLevelItem(otherCenterTreeRoot);
    tree->addTopLevelItem(memoryTreeRoot);
	tree->setContextMenuPolicy(Qt::CustomContextMenu);
    standardStationTreeRoot->setExpanded(true);
    otherCenterTreeRoot->setExpanded(true);
}
