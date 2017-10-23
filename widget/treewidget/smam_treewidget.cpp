#include <QGraphicsScene>
#include <QMessageBox>
#include <QMenu>
#include <QFile>
#include <QDebug>

#include "smam_treewidget.h"
#include "common_treeitem.h"
#include "main_component_header.h"

#include "widget/centerinfo_widget.h"
#include "widget/igmasdatacenter_widget.h"
#include "widget/igmasstationinfo_widget.h"
#include "widget/standardstationinfo_widget.h"
#include "widget/receiverinfo_widget.h"
#include "widget/sharedmemoryinfo_widget.h"

#include "widget/dialog/igmasdatacenter_edit_dialog.h"
#include "widget/dialog/igmasstation_edit_dialog.h"
#include "widget/dialog/othercenter_edit_dialog.h"
#include "widget/dialog/receiver_edit_dialog.h"
#include "widget/dialog/standardstation_edit_dialog.h"

#define STANDARDROOT_TREEITEM_TYPE 00
#define STANDARDNODE_TREEITEM_TYPE 01
#define RECEIVER_TREEITEM_TYPE 02

#define IGMASSTATIONROOT_TREEITEM_TYPE 10
#define IGMASSTATIONNODE_TREEITEM_TYPE 11

#define IGMASDATACENTERROOT_TREEITEM_TYPE 20
#define IGMASDATACENTERNODE_TREEITEM_TYPE 21

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
    systemMonitorWidget = new MainMonitorWidget();
    currentContentWidget = systemMonitorWidget;
    container->addWidget(currentContentWidget);
    connect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenu(QPoint)));
    connect(tree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(handleItemClicked(QTreeWidgetItem*)));
    connect(tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(handleItemDoubleClicked(QTreeWidgetItem*)));

    registerSignalSender(this);
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
            QAction* addNewStandardStation = new QAction(tr("添加基准站"), this);
            connect(addNewStandardStation, SIGNAL(triggered(bool)), this, SLOT(showAddNewStandardStationDialog()));
            popMenu->addAction(addNewStandardStation);
            break;
        }
        case STANDARDNODE_TREEITEM_TYPE:
        {
            QAction* addNewReceiver = new QAction(tr("添加接收机"), this);
            connect(addNewReceiver, SIGNAL(triggered(bool)), this, SLOT(showAddNewReceiverDialog()));
            popMenu->addAction(addNewReceiver);
            QAction* modifyStandardStation = new QAction(tr("编辑基准站"), this);
            connect(modifyStandardStation, SIGNAL(triggered(bool)), this, SLOT(showModifyStandardStationDialog()));
            popMenu->addAction(modifyStandardStation);
            QAction* deleteStandardStation = new QAction(tr("删除基准站"), this);
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
            QAction* modifyReceiver = new QAction(tr("编辑接收机"), this);
            connect(modifyReceiver, SIGNAL(triggered(bool)), this, SLOT(showModifyReceiverDialog()));
            popMenu->addAction(modifyReceiver);
            QAction* deleteReceiver = new QAction(tr("删除接收机"), this);
            connect(deleteReceiver, SIGNAL(triggered(bool)), this, SLOT(deleteReceiver()));
            popMenu->addAction(deleteReceiver);
            break;
        }
        case IGMASSTATIONROOT_TREEITEM_TYPE:
        {
            QAction* addNewIGMASStation = new QAction(tr("添加iGMAS测站"), this);
            connect(addNewIGMASStation, SIGNAL(triggered(bool)), this, SLOT(showAddNewIGMASStationDialog()));
            popMenu->addAction(addNewIGMASStation);
            break;
        }
        case IGMASSTATIONNODE_TREEITEM_TYPE:
        {
            int index = tree->currentIndex().row();
            if (ConfigHelper::iGMASStations[index]->getIsAvailable()) {
                QAction* stopIGMASStation = new QAction(tr("停止iGMAS测站"), this);
                connect(stopIGMASStation, SIGNAL(triggered(bool)), this, SLOT(stopIGMASStation()));
                popMenu->addAction(stopIGMASStation);
            }
            else {
                QAction* startIGMASStation = new QAction(tr("启动iGMAS测站"), this);
                connect(startIGMASStation, SIGNAL(triggered(bool)), this, SLOT(startIGMASStation()));
                popMenu->addAction(startIGMASStation);
            }
            QAction* modifyIGMASStation = new QAction(tr("编辑iGMAS测站"), this);
            connect(modifyIGMASStation, SIGNAL(triggered(bool)), this, SLOT(showModifyIGMASStationDialog()));
            popMenu->addAction(modifyIGMASStation);
            QAction* deleteIGMASStation = new QAction(tr("删除iGMAS测站"), this);
            connect(deleteIGMASStation, SIGNAL(triggered(bool)), this, SLOT(deleteIGMASStation()));
            popMenu->addAction(deleteIGMASStation);
            break;
        }
        case IGMASDATACENTERROOT_TREEITEM_TYPE:
        {
            QAction* addNewIGMASDataCenter = new QAction(tr("添加iGMAS数据中心"), this);
            connect(addNewIGMASDataCenter, SIGNAL(triggered(bool)), this, SLOT(showAddNewIGMASDataCenterDialog()));
            popMenu->addAction(addNewIGMASDataCenter);
            break;
        }
        case IGMASDATACENTERNODE_TREEITEM_TYPE:
        {
            QAction* modifyIGMASDataCenter = new QAction(tr("编辑iGMAS数据中心"), this);
            connect(modifyIGMASDataCenter, SIGNAL(triggered(bool)), this, SLOT(showModifyIGMASDataCenterDialog()));
            popMenu->addAction(modifyIGMASDataCenter);
            QAction* deleteIGMASDataCenter = new QAction(tr("删除iGMAS数据中心"), this);
            connect(deleteIGMASDataCenter, SIGNAL(triggered(bool)), this, SLOT(deleteIGMASDataCenter()));
            popMenu->addAction(deleteIGMASDataCenter);
            break;
        }
        case CENTERROOT_TREEITEM_TYPE:
        {
            QAction* addNewCenter = new QAction(tr("添加数据中心"), this);
            connect(addNewCenter, SIGNAL(triggered(bool)), this, SLOT(showAddNewOtherCenterDialog()));
            popMenu->addAction(addNewCenter);
            break;
        }
        case CENTERNODE_TREEITEM_TYPE:
        {
            QAction* modifyCenter = new QAction(tr("编辑数据中心"), this);
            connect(modifyCenter, SIGNAL(triggered(bool)), this, SLOT(showModifyOtherCenterDialog()));
            popMenu->addAction(modifyCenter);
            QAction* deleteCenter = new QAction(tr("删除数据中心"), this);
            connect(deleteCenter, SIGNAL(triggered(bool)), this, SLOT(deleteOtherCenter()));
            popMenu->addAction(deleteCenter);
            break;
        }
    }
	popMenu->exec(QCursor::pos());
}

void SMAMTreeWidget::handleItemClicked(QTreeWidgetItem* item)
{
    switch (item->type()) {
        case STANDARDROOT_TREEITEM_TYPE:
        case IGMASSTATIONROOT_TREEITEM_TYPE:
        case IGMASDATACENTERROOT_TREEITEM_TYPE:
        case CENTERROOT_TREEITEM_TYPE:
            if (currentContentWidget != systemMonitorWidget) {
                container->removeWidget(currentContentWidget);
                delete currentContentWidget;
            }
            currentContentWidget = systemMonitorWidget;
            systemMonitorWidget->show();
            break;
        case MEMINFO_TREEITEM_TYPE:
            if (currentContentWidget != systemMonitorWidget) {
                container->removeWidget(currentContentWidget);
                delete currentContentWidget;
            }
            systemMonitorWidget->hide();
            currentContentWidget = new SharedMemoryInfoWidget();
            container->addWidget(currentContentWidget);
            break;
        default:
            break;
    }
}

void SMAMTreeWidget::handleItemDoubleClicked(QTreeWidgetItem* item)
{
    if (currentContentWidget) {
        if (currentContentWidget == systemMonitorWidget) {
            systemMonitorWidget->hide();
        }
        else {
            container->removeWidget(currentContentWidget);
            delete currentContentWidget;
        }
    }

    int index = tree->currentIndex().row(), parentIndex;
    switch (item->type()) {
        case STANDARDNODE_TREEITEM_TYPE:
            currentContentWidget = new StandardStationInfoWidget();
            ((StandardStationInfoWidget*) currentContentWidget)->setStation(ConfigHelper::standardStations[index]);
			break;
        case RECEIVER_TREEITEM_TYPE:
			currentContentWidget = new ReceiverInfoWidget();
            parentIndex = standardStationTreeRoot->indexOfChild(tree->currentItem()->parent());
            ((ReceiverInfoWidget*) currentContentWidget)->setReceiver(ConfigHelper::standardStations[parentIndex]->getReceivers()[index]);
			break;
        case IGMASSTATIONNODE_TREEITEM_TYPE:
            currentContentWidget = new iGMASStationInfoWidget();
            ((iGMASStationInfoWidget*) currentContentWidget)->setStation(ConfigHelper::iGMASStations[index]);
            break;
        case IGMASDATACENTERNODE_TREEITEM_TYPE:
            currentContentWidget = new iGMASDataCenterWidget();
            ((iGMASDataCenterWidget*) currentContentWidget)->setDataCenter(ConfigHelper::iGMASDataCenters[index]);
            break;
        case CENTERNODE_TREEITEM_TYPE:
            currentContentWidget = new CenterInfoWidget();
            ((CenterInfoWidget*) currentContentWidget)->setCenter(ConfigHelper::otherCenters[index]);
            break;
        case MEMINFO_TREEITEM_TYPE:
            currentContentWidget = new SharedMemoryInfoWidget();
            break;
		default:
			currentContentWidget = 0;
			break;
	}
	if (currentContentWidget) {
        if (currentContentWidget == systemMonitorWidget) {
            systemMonitorWidget->show();
        }
        else {
            container->addWidget(currentContentWidget);
        }
	}
    else {
        container->addWidget(new QWidget());
	}
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
    systemMonitorWidget->updateView();
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
    ConfigHelper::update();
    systemMonitorWidget->updateView();
    //addWidgetToContainer(tree->currentItem());
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
        systemMonitorWidget->updateView();
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
    systemMonitorWidget->updateView();
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
    systemMonitorWidget->updateView();
    //addWidgetToContainer(tree->currentItem());
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
        systemMonitorWidget->updateView();
        delete tree->currentItem()->parent()->takeChild(index);
    }
}

void SMAMTreeWidget::showAddNewIGMASStationDialog()
{
    if (ConfigHelper::iGMASStations.size() > IGMASSTATION_MAXITEMCOUNT) {
        QMessageBox box(QMessageBox::Warning, tr("提示"), tr("超过最大单个中心所能容纳的iGMAS站数目。"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok , tr("确认"));
        box.exec();
    }
    else {
        iGMASStationEditDialog* dialog = new iGMASStationEditDialog(tree);
        connect(dialog, SIGNAL(confirmButtonClicked(iGMASStation*)), this, SLOT(addNewIGMASStation(iGMASStation*)));
        dialog->show();
    }
}

void SMAMTreeWidget::addNewIGMASStation(iGMASStation* station)
{
    station->setMemID(ConfigHelper::findFreeIGMASStationMemID());
    ConfigHelper::iGMASStations << station;
    ConfigHelper::update();
    systemMonitorWidget->updateView();
    tree->currentItem()->addChild(new CommonTreeItem(IGMASSTATIONNODE_TREEITEM_TYPE, station->getDescription(), ":/igmas_station"));
    emit iGMASStationAdded(station->getBufferItem());
}

void SMAMTreeWidget::startIGMASStation()
{
    int index = tree->currentIndex().row();
    iGMASStation* station = ConfigHelper::iGMASStations[index];
    station->setIsAvailable(true);
    ConfigHelper::update();
    emit iGMASStationStarted(station->getMemID());
}

void SMAMTreeWidget::stopIGMASStation()
{
    int index = tree->currentIndex().row();
    iGMASStation* station = ConfigHelper::iGMASStations[index];
    station->setIsAvailable(false);
    ConfigHelper::update();
    emit iGMASStationStoped(station->getMemID());
}

void SMAMTreeWidget::showModifyIGMASStationDialog()
{
    int index = tree->currentIndex().row();
    iGMASStationEditDialog* dialog = new iGMASStationEditDialog(ConfigHelper::iGMASStations[index], tree);
    connect(dialog, SIGNAL(confirmButtonClicked(iGMASStation*)), this, SLOT(modifyIGMASStation(iGMASStation*)));
    dialog->show();
}

void SMAMTreeWidget::modifyIGMASStation(iGMASStation* station)
{
    ConfigHelper::update();
    systemMonitorWidget->updateView();
    //addWidgetToContainer(tree->currentItem());
    tree->currentItem()->setText(0, station->getStationName());
    emit iGMASStationModified(station->getMemID());
}

void SMAMTreeWidget::deleteIGMASStation()
{
    int index = tree->currentIndex().row();
    iGMASStation* station = ConfigHelper::iGMASStations[index];
    QString content = tr("确认删除iGMAS测站<") + station->getDescription() + tr(">吗？");
    QMessageBox box(QMessageBox::Warning, tr("提示"), content);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::No , tr("取消"));
    box.setButtonText(QMessageBox::Yes , tr("确认"));
    if (box.exec() == QMessageBox::Yes) {

        ConfigHelper::clearIGMASStationMemID(station->getMemID());
        ConfigHelper::iGMASStations.removeAt(index);
        ConfigHelper::update();
        systemMonitorWidget->updateView();
        emit iGMASStationDeleted(station->getMemID());
        delete tree->currentItem()->parent()->takeChild(index);
        delete station;

    }
}

void SMAMTreeWidget::showAddNewIGMASDataCenterDialog()
{
    if (ConfigHelper::iGMASDataCenters.size() > IGMASDATACENTER_MAXITEMCOUNT) {
        QMessageBox box(QMessageBox::Warning, tr("提示"), tr("超过最大单个中心所能容纳的iGMAS数据中心数目。"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok , tr("确认"));
        box.exec();
    }
    else {
        iGMASDataCenterEditDialog* dialog = new iGMASDataCenterEditDialog(tree);
        connect(dialog, SIGNAL(confirmButtonClicked(iGMASDataCenter*)), this, SLOT(addNewIGMASDataCenter(iGMASDataCenter*)));
        dialog->show();
    }
}

void SMAMTreeWidget::addNewIGMASDataCenter(iGMASDataCenter* dataCenter)
{
    dataCenter->setCenterID(ConfigHelper::getNewIGMASDataCenterID());
    ConfigHelper::iGMASDataCenters << dataCenter;
    ConfigHelper::update();
    systemMonitorWidget->updateView();
    tree->currentItem()->addChild(new CommonTreeItem(IGMASDATACENTERNODE_TREEITEM_TYPE, dataCenter->getCenterName(), ":/datacenter"));
    emit iGMASDataCenterAdded(dataCenter->getBufferItem());
}

void SMAMTreeWidget::showModifyIGMASDataCenterDialog()
{
    int index = tree->currentIndex().row();
    iGMASDataCenterEditDialog* dialog = new iGMASDataCenterEditDialog(ConfigHelper::iGMASDataCenters[index], tree);
    connect(dialog, SIGNAL(confirmButtonClicked(iGMASDataCenter*)), this, SLOT(modifyIGMASDataCenter(iGMASDataCenter*)));
    dialog->show();
}

void SMAMTreeWidget::modifyIGMASDataCenter(iGMASDataCenter* dataCenter)
{
    ConfigHelper::update();
    systemMonitorWidget->updateView();
    //addWidgetToContainer(tree->currentItem());
    tree->currentItem()->setText(0, dataCenter->getCenterName());
    emit iGMASDataCenterModified(dataCenter->getCenterID());
}

void SMAMTreeWidget::deleteIGMASDataCenter()
{
    int index = tree->currentIndex().row();
    iGMASDataCenter* dataCenter = ConfigHelper::iGMASDataCenters[index];
    QString content = tr("移除iGMAS数据中心将导致某些iGMAS测站断线重连！\n确认删除iGMAS数据中心<") + dataCenter->getCenterName() + tr(">吗？");
    QMessageBox box(QMessageBox::Warning, tr("提示"), content);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::No , tr("取消"));
    box.setButtonText(QMessageBox::Yes , tr("确认"));
    if (box.exec() == QMessageBox::Yes) {

        ConfigHelper::iGMASDataCenters.removeAt(index);
        ConfigHelper::deleteIGMASDataCenter(dataCenter->getCenterID());
        ConfigHelper::update();
        systemMonitorWidget->updateView();
        emit iGMASDataCenterDeleted(dataCenter->getCenterID());
        delete tree->currentItem()->parent()->takeChild(index);
        delete dataCenter;

    }
}

void SMAMTreeWidget::showAddNewOtherCenterDialog()
{
    if (ConfigHelper::otherCenters.size() > OTHERCENTER_MAXITEMCOUNT) {
        QMessageBox box(QMessageBox::Warning, tr("提示"), tr("超过最大数据中心数目。"));
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
    systemMonitorWidget->updateView();
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
    ConfigHelper::update();
    systemMonitorWidget->updateView();
    //addWidgetToContainer(tree->currentItem());
    tree->currentItem()->setText(0, center->getCenterName());
    emit OtherCenterModified(center->getCenterID());
}

void SMAMTreeWidget::deleteOtherCenter()
{
    int index = tree->currentIndex().row();
    OtherCenter* center = ConfigHelper::otherCenters[index];
    QString content = tr("确认删除数据中心<") + center->getCenterName() + tr(">吗？");
    QMessageBox box(QMessageBox::Warning, "提示", content);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::No , tr("取消"));
    box.setButtonText(QMessageBox::Yes , tr("确认"));
    if (box.exec() == QMessageBox::Yes) {
        ConfigHelper::otherCenters.removeAt(index);
        ConfigHelper::update();
        systemMonitorWidget->updateView();
        emit OtherCenterDeleted(center->getCenterID());
        delete tree->currentItem()->parent()->takeChild(tree->currentIndex().row());
        delete center;
    }
}

void SMAMTreeWidget::initAtBJ()
{
    iGMASStationTreeRoot = new CommonTreeItem(IGMASSTATIONROOT_TREEITEM_TYPE, tr("iGMAS测站"), ":/igmas_root");
    for (int i = 0; i < ConfigHelper::iGMASStations.size(); i++) {
        iGMASStation* station = ConfigHelper::iGMASStations[i];
        iGMASStationTreeRoot->addChild(new CommonTreeItem(IGMASSTATIONNODE_TREEITEM_TYPE, station->getDescription(), ":/igmas_station"));
    }

    iGMASDataCenterTreeRoot = new CommonTreeItem(IGMASDATACENTERROOT_TREEITEM_TYPE, tr("iGMAS数据中心"), ":/datacenter_root");
    for (int i = 0; i < ConfigHelper::iGMASDataCenters.size(); i++) {
        iGMASDataCenter* center = ConfigHelper::iGMASDataCenters[i];
        iGMASDataCenterTreeRoot->addChild(new CommonTreeItem(IGMASDATACENTERNODE_TREEITEM_TYPE, center->getCenterName(), ":/datacenter"));
    }

    otherCenterTreeRoot = new CommonTreeItem(CENTERROOT_TREEITEM_TYPE, tr("接收机数据中心"), ":/center_root");
    for (int i = 0; i < ConfigHelper::otherCenters.size(); i++) {
        OtherCenter* center = ConfigHelper::otherCenters[i];
        otherCenterTreeRoot->addChild(new CommonTreeItem(CENTERNODE_TREEITEM_TYPE, center->getCenterName(), ":/other_center"));
    }

    memoryTreeRoot = new CommonTreeItem(MEMINFO_TREEITEM_TYPE, tr("内存管理"), ":/2");

    tree->setColumnCount(1);
    tree->addTopLevelItem(iGMASStationTreeRoot);
    tree->addTopLevelItem(iGMASDataCenterTreeRoot);
    tree->addTopLevelItem(otherCenterTreeRoot);
    tree->addTopLevelItem(memoryTreeRoot);
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    iGMASStationTreeRoot->setExpanded(true);
    iGMASDataCenterTreeRoot->setExpanded(true);
    otherCenterTreeRoot->setExpanded(true);
}

void SMAMTreeWidget::initAtXJ()
{
    standardStationTreeRoot = new CommonTreeItem(STANDARDROOT_TREEITEM_TYPE, tr("基准站管理"), ":/standard_root");
    for (int i = 0; i < ConfigHelper::standardStations.size(); i++) {
        StandardStation* station = ConfigHelper::standardStations[i];
        QTreeWidgetItem* stationTreeItem = new CommonTreeItem(STANDARDNODE_TREEITEM_TYPE, station->getStationName(), ":/standard_station");
        standardStationTreeRoot->addChild(stationTreeItem);
        for (int j = 0; j < station->getReceivers().size(); j++) {
            Receiver* receiver = station->getReceivers()[j];
            stationTreeItem->addChild(new CommonTreeItem(RECEIVER_TREEITEM_TYPE, receiver->getReceiverName(), ":/standard_receiver"));
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
