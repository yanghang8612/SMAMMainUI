#include <QGraphicsScene>
#include <QMessageBox>
#include <QMenu>
#include <QFile>
#include <QDebug>

#include "main_component_header.h"
#include "smam_treewidget.h"
#include "widget/centerinfo_widget.h"
#include "widget/igmasstationinfo_widget.h"
#include "widget/mainmonitor_widget.h"
#include "widget/standardstationinfo_widget.h"
#include "widget/receiverinfo_widget.h"
#include "widget/sharedmemoryinfo_widget.h"
#include "widget/dialog/add_center_dialog.h"
#include "widget/dialog/modify_center_dialog.h"
#include "widget/dialog/add_receiver_dialog.h"
#include "widget/dialog/modify_receiver_dialog.h"
#include "widget/dialog/add_standardstation_dialog.h"
#include "widget/dialog/modify_standardstation_dialog.h"
#include "widget/dialog/add_igmasstation_dialog.h"
#include "widget/dialog/modify_igmasstation_dialog.h"

#define STANDARDROOT_TREEITEM_TYPE 00
#define STANDARDNODE_TREEITEM_TYPE 01
#define RECEIVER_TREEITEM_TYPE 02

#define IGMASROOT_TREEITEM_TYPE 10
#define IGMASNODE_TREEITEM_TYPE 11

#define IGSROOT_TREEITEM_TYPE 20
#define IGSNODE_TREEITEM_TYPE 21

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
            qDebug() << "No match deploymenttype.";
            break;
    }
    systemMonitorWidget = new MainMonitorWidget(&standardStationList, &otherCenterList);
    currentContentWidget = systemMonitorWidget;
    container->addWidget(currentContentWidget);
    connect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenu(QPoint)));
    connect(tree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(addWidgetToContainer(QTreeWidgetItem*)));
}

void SMAMTreeWidget::showRightMenu(QPoint pos)
{
	QTreeWidgetItem* curItem = tree->itemAt(pos);
	if (curItem == NULL)
		return;
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
            QAction* startReceiver = new QAction(tr("启动接收机"), this);
            popMenu->addAction(startReceiver);
            QAction* stopReceiver = new QAction(tr("停止接收机"), this);
            popMenu->addAction(stopReceiver);
            QAction* modifyReceiver = new QAction(tr("编辑接收机"), this);
            connect(modifyReceiver, SIGNAL(triggered(bool)), this, SLOT(showModifyReceiverDialog()));
            popMenu->addAction(modifyReceiver);
            QAction* deleteReceiver = new QAction(tr("删除接收机"), this);
            connect(deleteReceiver, SIGNAL(triggered(bool)), this, SLOT(deleteReceiver()));
            popMenu->addAction(deleteReceiver);
            break;
        }
        case IGMASROOT_TREEITEM_TYPE:
        {
            QAction* addNewIGMASStation = new QAction(tr("添加iGMAS测站"), this);
            connect(addNewIGMASStation, SIGNAL(triggered(bool)), this, SLOT(showAddNewIGMASStationDialog()));
            popMenu->addAction(addNewIGMASStation);
            break;
        }
        case IGMASNODE_TREEITEM_TYPE:
        {
            QAction* modifyIGMASStation = new QAction(tr("编辑iGMAS测站"), this);
            connect(modifyIGMASStation, SIGNAL(triggered(bool)), this, SLOT(showModifyIGMASStationDialog()));
            popMenu->addAction(modifyIGMASStation);
            QAction* deleteIGMASStation = new QAction(tr("删除iGMAS测站"), this);
            connect(deleteIGMASStation, SIGNAL(triggered(bool)), this, SLOT(deleteIGMASStation()));
            popMenu->addAction(deleteIGMASStation);
            break;
        }
        case IGSROOT_TREEITEM_TYPE:
        {
            QAction* addNewIGSStation = new QAction(tr("添加iGS测站"), this);
            connect(addNewIGSStation, SIGNAL(triggered(bool)), this, SLOT(showAddNewIGSStationDialog()));
            popMenu->addAction(addNewIGSStation);
            break;
        }
        case IGSNODE_TREEITEM_TYPE:
        {
            QAction* modifyIGSStation = new QAction(tr("编辑iGS测站"), this);
            connect(modifyIGSStation, SIGNAL(triggered(bool)), this, SLOT(showModifyIGSStationDialog()));
            popMenu->addAction(modifyIGSStation);
            QAction* deleteIGSStation = new QAction(tr("删除iGS测站"), this);
            connect(deleteIGSStation, SIGNAL(triggered(bool)), this, SLOT(deleteIGSStation()));
            popMenu->addAction(deleteIGSStation);
            break;
        }
        case CENTERROOT_TREEITEM_TYPE:
        {
            QAction* addNewCenter = new QAction(tr("添加其他中心"), this);
            connect(addNewCenter, SIGNAL(triggered(bool)), this, SLOT(showAddNewCenterDialog()));
            popMenu->addAction(addNewCenter);
            break;
        }
        case CENTERNODE_TREEITEM_TYPE:
        {
            QAction* modifyCenter = new QAction(tr("编辑其他中心"), this);
            connect(modifyCenter, SIGNAL(triggered(bool)), this, SLOT(showModifyCenterDialog()));
            popMenu->addAction(modifyCenter);
            QAction* deleteCenter = new QAction(tr("删除其他中心"), this);
            connect(deleteCenter, SIGNAL(triggered(bool)), this, SLOT(deleteCenter()));
            popMenu->addAction(deleteCenter);
            break;
        }
        default:
            break;
    }
	popMenu->exec(QCursor::pos());
}

void SMAMTreeWidget::addWidgetToContainer(QTreeWidgetItem* item)
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
    switch (item->type()) {
        case STANDARDROOT_TREEITEM_TYPE:
        case IGMASROOT_TREEITEM_TYPE:
        case IGSROOT_TREEITEM_TYPE:
        case CENTERROOT_TREEITEM_TYPE:
            currentContentWidget = systemMonitorWidget;
            break;
        case STANDARDNODE_TREEITEM_TYPE:
            currentContentWidget = new StandardStationInfoWidget();
            ((StandardStationInfoWidget*) currentContentWidget)->setStation((StandardStation*) item->data(0, Qt::UserRole).value<void*>());
			break;
        case RECEIVER_TREEITEM_TYPE:
			currentContentWidget = new ReceiverInfoWidget();
			((ReceiverInfoWidget*) currentContentWidget)->setReceiver((Receiver*) item->data(0, Qt::UserRole).value<void*>());
			break;
        case IGMASNODE_TREEITEM_TYPE:
            currentContentWidget = new IGMASStationInfoWidget();
            ((IGMASStationInfoWidget*) currentContentWidget)->setStation((IGMASStation*) item->data(0, Qt::UserRole).value<void*>());
            break;
        case IGSNODE_TREEITEM_TYPE:
            break;
        case CENTERNODE_TREEITEM_TYPE:
            currentContentWidget = new CenterInfoWidget();
            ((CenterInfoWidget*) currentContentWidget)->setCenter((OtherCenter*) item->data(0, Qt::UserRole).value<void*>());
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
	AddStandardStationDialog* dialog = new AddStandardStationDialog(tree);
	connect(dialog, SIGNAL(confirmButtonClicked(StandardStation*)), this, SLOT(addNewStandardStation(StandardStation*)));
	dialog->show();
}

void SMAMTreeWidget::addNewStandardStation(StandardStation* station)
{
    standardStationList << station;
    tree->currentItem()->addChild(new StandardTreeWidgetItem(tree->currentItem(), STANDARDNODE_TREEITEM_TYPE, station));

	QDomElement newStandardStation = root.createElement("STATION");

	QDomElement stationName = root.createElement("STATIONNAME");
	stationName.appendChild(root.createTextNode(station->getStationName()));
	newStandardStation.appendChild(stationName);

	QDomElement stationIP = root.createElement("IPADDRESS");
	stationIP.appendChild(root.createTextNode(station->getIpAddress()));
	newStandardStation.appendChild(stationIP);

	QDomElement stationPort = root.createElement("IPPORT");
	stationPort.appendChild(root.createTextNode(QString::number(station->getPort())));
	newStandardStation.appendChild(stationPort);

	QDomElement stationMode = root.createElement("STATIONMODE");
	stationMode.appendChild(root.createTextNode(QString::number((int) station->getMode())));
	newStandardStation.appendChild(stationMode);

	QDomElement stationThreadCount = root.createElement("SERVICETHREADCOUNT");
	stationThreadCount.appendChild(root.createTextNode(QString::number(station->getServiceThreadCount())));
	newStandardStation.appendChild(stationThreadCount);

	QDomElement stationType = root.createElement("DEPLOYMENTTYPE");
    stationType.appendChild(root.createTextNode(QString::number((int) deploymentType)));
	newStandardStation.appendChild(stationType);

	QDomElement stationDetail = root.createElement("DETAIL");
	stationDetail.appendChild(root.createTextNode(station->getDetail()));
	newStandardStation.appendChild(stationDetail);

	QDomElement receiverList = root.createElement("RECEIVERS");
	newStandardStation.appendChild(receiverList);

    standardStationRoot.appendChild(newStandardStation);

	writeConfigFile();
}

void SMAMTreeWidget::showModifyStandardStationDialog()
{
    ModifyStandardStationDialog* dialog = new ModifyStandardStationDialog((StandardStation*) tree->currentItem()->data(0, Qt::UserRole).value<void*>(), tree);
	connect(dialog, SIGNAL(confirmButtonClicked(StandardStation*)), this, SLOT(modifyStandardStation(StandardStation*)));
	dialog->show();
}

void SMAMTreeWidget::modifyStandardStation(StandardStation* station)
{
	addWidgetToContainer(tree->currentItem());

	int index = tree->currentIndex().row();
    QDomNode standardStationNode = standardStationRoot.childNodes().at(index);

	QDomElement stationName = root.createElement("STATIONNAME");
	stationName.appendChild(root.createTextNode(station->getStationName()));
	standardStationNode.replaceChild(stationName, standardStationNode.namedItem("STATIONNAME"));

	QDomElement stationIP = root.createElement("IPADDRESS");
	stationIP.appendChild(root.createTextNode(station->getIpAddress()));
	standardStationNode.replaceChild(stationIP, standardStationNode.namedItem("IPADDRESS"));

	QDomElement stationPort = root.createElement("IPPORT");
	stationPort.appendChild(root.createTextNode(QString::number(station->getPort())));
	standardStationNode.replaceChild(stationPort, standardStationNode.namedItem("IPPORT"));

	QDomElement stationMode = root.createElement("STATIONMODE");
	stationMode.appendChild(root.createTextNode(QString::number((int) station->getMode())));
	standardStationNode.replaceChild(stationMode, standardStationNode.namedItem("STATIONMODE"));

	QDomElement stationThreadCount = root.createElement("SERVICETHREADCOUNT");
	stationThreadCount.appendChild(root.createTextNode(QString::number(station->getServiceThreadCount())));
	standardStationNode.replaceChild(stationThreadCount, standardStationNode.namedItem("SERVICETHREADCOUNT"));

	QDomElement stationType = root.createElement("DEPLOYMENTTYPE");
    stationType.appendChild(root.createTextNode(QString::number((int) deploymentType)));
	standardStationNode.replaceChild(stationType, standardStationNode.namedItem("DEPLOYMENTTYPE"));

	QDomElement stationDetail = root.createElement("DETAIL");
	stationDetail.appendChild(root.createTextNode(station->getDetail()));
	standardStationNode.replaceChild(stationDetail, standardStationNode.namedItem("DETAIL"));

	writeConfigFile();
}

void SMAMTreeWidget::deleteStandardStation()
{
	StandardStation* station = (StandardStation*) tree->currentItem()->data(0, Qt::UserRole).value<void*>();\
    QString content = tr("确认删除基准站 ") + station->getStationName() + tr(" 吗？");
	int ret = QMessageBox::warning(tree,
								   tr("提示"),
                                   content,
								   QMessageBox::Cancel | QMessageBox::Ok);
	if (ret == QMessageBox::Ok) {
        standardStationList.removeAt(tree->currentIndex().row());
        standardStationRoot.removeChild(standardStationRoot.childNodes().at(tree->currentIndex().row()));
		delete tree->currentItem()->parent()->takeChild(tree->currentIndex().row());
		writeConfigFile();
	}
}

void SMAMTreeWidget::showAddNewReceiverDialog()
{
    if ((quint32) ((StandardStation*) tree->currentItem()->data(0, Qt::UserRole).value<void*>())->getReceivers().size() > MAX_RECEIVER_COUNT_PERSTATION) {
        QMessageBox::warning(tree,
                             tr("提示"),
                             tr("超过最大单个基准站所能容纳接收机数目。"),
                             QMessageBox::Ok);
    }
    else {
        AddReceiverDialog* dialog = new AddReceiverDialog(tree);
        connect(dialog, SIGNAL(confirmButtonClicked(Receiver*)), this, SLOT(addNewReceiver(Receiver*)));
        dialog->show();
    }
}

void SMAMTreeWidget::addNewReceiver(Receiver* receiver)
{
    ((StandardStation*) tree->currentItem()->data(0, Qt::UserRole).value<void*>())->addReceiver(receiver);
    tree->currentItem()->addChild(new ReceiverTreeWidgetItem(tree->currentItem(), RECEIVER_TREEITEM_TYPE, receiver));

	QDomElement newReceiver = root.createElement("RECEIVER");

	QDomElement receiverName = root.createElement("RECEIVERNAME");
	receiverName.appendChild(root.createTextNode(receiver->getReceiverName()));
	newReceiver.appendChild(receiverName);

	QDomElement receiverIP = root.createElement("IPADDRESS");
	receiverIP.appendChild(root.createTextNode(receiver->getIpAddress()));
	newReceiver.appendChild(receiverIP);

	QDomElement receiverPort = root.createElement("IPPORT");
	receiverPort.appendChild(root.createTextNode(QString::number(receiver->getPort())));
	newReceiver.appendChild(receiverPort);

	QDomElement receiverLongitude = root.createElement("LONGITUDE");
	receiverLongitude.appendChild(root.createTextNode(QString::number(receiver->getLongitude())));
	newReceiver.appendChild(receiverLongitude);

	QDomElement receiverLatitude = root.createElement("LATITUDE");
	receiverLatitude.appendChild(root.createTextNode(QString::number(receiver->getLatitude())));
	newReceiver.appendChild(receiverLatitude);

    QDomElement receiverHeight = root.createElement("HEIGHT");
    receiverHeight.appendChild(root.createTextNode(QString::number(receiver->getHeight())));
    newReceiver.appendChild(receiverHeight);

    standardStationRoot.childNodes().at(tree->currentIndex().row()).namedItem("RECEIVERS").appendChild(newReceiver);

	writeConfigFile();
}

void SMAMTreeWidget::showModifyReceiverDialog()
{
    ModifyReceiverDialog* dialog = new ModifyReceiverDialog((Receiver*) tree->currentItem()->data(0, Qt::UserRole).value<void*>(), tree);
	connect(dialog, SIGNAL(confirmButtonClicked(Receiver*)), this, SLOT(modifyReceiver(Receiver*)));
	dialog->show();
}

void SMAMTreeWidget::modifyReceiver(Receiver* receiver)
{
	addWidgetToContainer(tree->currentItem());

    int parentNodeIndex = standardStationTreeRoot->indexOfChild(tree->currentItem()->parent());
	int nodeIndex = tree->currentIndex().row();
    QDomNode receiverNode = standardStationRoot.childNodes().at(parentNodeIndex).namedItem("RECEIVERS").childNodes().at(nodeIndex);

	QDomElement receiverName = root.createElement("RECEIVERNAME");
	receiverName.appendChild(root.createTextNode(receiver->getReceiverName()));
	receiverNode.replaceChild(receiverName, receiverNode.namedItem("RECEIVERNAME"));

	QDomElement receiverIP = root.createElement("IPADDRESS");
	receiverIP.appendChild(root.createTextNode(receiver->getIpAddress()));
	receiverNode.replaceChild(receiverIP, receiverNode.namedItem("IPADDRESS"));

	QDomElement receiverPort = root.createElement("IPPORT");
	receiverPort.appendChild(root.createTextNode(QString::number(receiver->getPort())));
	receiverNode.replaceChild(receiverPort, receiverNode.namedItem("IPPORT"));

	QDomElement receiverLongitude = root.createElement("LONGITUDE");
	receiverLongitude.appendChild(root.createTextNode(QString::number(receiver->getLongitude())));
	receiverNode.replaceChild(receiverLongitude, receiverNode.namedItem("LONGITUDE"));

	QDomElement receiverLatitude = root.createElement("LATITUDE");
	receiverLatitude.appendChild(root.createTextNode(QString::number(receiver->getLatitude())));
	receiverNode.replaceChild(receiverLatitude, receiverNode.namedItem("LATITUDE"));

    QDomElement receiverHeight = root.createElement("HEIGHT");
    receiverHeight.appendChild(root.createTextNode(QString::number(receiver->getHeight())));
    receiverNode.replaceChild(receiverHeight, receiverNode.namedItem("HEIGHT"));

	writeConfigFile();
}

void SMAMTreeWidget::deleteReceiver()
{
	Receiver* receiver = (Receiver*) tree->currentItem()->data(0, Qt::UserRole).value<void*>();\
    QString content = tr("确认删除接受机 ") + receiver->getReceiverName() + tr(" 吗？");
	int ret = QMessageBox::warning(tree,
								   tr("提示"),
                                   content,
								   QMessageBox::Cancel | QMessageBox::Ok);
	if (ret == QMessageBox::Ok) {
        int parentNodeIndex = standardStationTreeRoot->indexOfChild(tree->currentItem()->parent());
        standardStationList.at(parentNodeIndex)->removerReceiver(tree->currentIndex().row());
        QDomNode parentNode = standardStationRoot.childNodes().at(parentNodeIndex).namedItem("RECEIVERS");
		parentNode.removeChild(parentNode.childNodes().at(tree->currentIndex().row()));
		delete tree->currentItem()->parent()->takeChild(tree->currentIndex().row());
		writeConfigFile();
    }
}

void SMAMTreeWidget::showAddNewIGMASStationDialog()
{
    AddIGMASStationDialog* dialog = new AddIGMASStationDialog(tree);
    connect(dialog, SIGNAL(confirmButtonClicked(IGMASStation*)), this, SLOT(addNewIGMASStation(IGMASStation*)));
    dialog->show();
}

void SMAMTreeWidget::addNewIGMASStation(IGMASStation* station)
{
    iGMASStationList << station;
    tree->currentItem()->addChild(new IGMASTreeWidgetItem(tree->currentItem(), IGMASNODE_TREEITEM_TYPE, station));

    QDomElement newIGMASStation = root.createElement("STATION");

    QDomElement stationAvailable = root.createElement("ISAVAILABLE");
    stationAvailable.appendChild(root.createTextNode((station->getIsAvailable()) ? "1" : "0"));
    newIGMASStation.appendChild(stationAvailable);

    QDomElement stationIP = root.createElement("IPADDRESS");
    stationIP.appendChild(root.createTextNode(station->getIpAddress()));
    newIGMASStation.appendChild(stationIP);

    QDomElement stationPort = root.createElement("IPPORT");
    stationPort.appendChild(root.createTextNode(QString::number(station->getPort())));
    newIGMASStation.appendChild(stationPort);

    QDomElement stationMount = root.createElement("MOUNT");
    stationMount.appendChild(root.createTextNode(station->getMount()));
    newIGMASStation.appendChild(stationMount);

    QDomElement stationMemID = root.createElement("MEMID");
    stationMemID.appendChild(root.createTextNode(QString::number(station->getMemID())));
    newIGMASStation.appendChild(stationMemID);

    QDomElement stationLongitude = root.createElement("LONGITUDE");
    stationLongitude.appendChild(root.createTextNode(QString::number(station->getLongitude())));
    newIGMASStation.appendChild(stationLongitude);

    QDomElement stationLatitude = root.createElement("LATITUDE");
    stationLatitude.appendChild(root.createTextNode(QString::number(station->getLatitude())));
    newIGMASStation.appendChild(stationLatitude);

    QDomElement stationHeight = root.createElement("HEIGHT");
    stationHeight.appendChild(root.createTextNode(QString::number(station->getHeight())));
    newIGMASStation.appendChild(stationHeight);

    iGMASStationRoot.appendChild(newIGMASStation);

    writeConfigFile();
}

void SMAMTreeWidget::showModifyIGMASStationDialog()
{
    ModifyIGMASStationDialog* dialog = new ModifyIGMASStationDialog((IGMASStation*) tree->currentItem()->data(0, Qt::UserRole).value<void*>(), tree);
    connect(dialog, SIGNAL(confirmButtonClicked(IGMASStation*)), this, SLOT(modifyIGMASStation(IGMASStation*)));
    dialog->show();
}

void SMAMTreeWidget::modifyIGMASStation(IGMASStation* station)
{
    addWidgetToContainer(tree->currentItem());

    int index = tree->currentIndex().row();
    QDomNode iGMASStationNode = iGMASStationRoot.childNodes().at(index);

    QDomElement stationAvailable = root.createElement("ISAVAILABLE");
    stationAvailable.appendChild(root.createTextNode((station->getIsAvailable()) ? "1" : "0"));
    iGMASStationNode.replaceChild(stationAvailable, iGMASStationNode.namedItem("ISAVAILABLE"));

    QDomElement stationIP = root.createElement("IPADDRESS");
    stationIP.appendChild(root.createTextNode(station->getIpAddress()));
    iGMASStationNode.replaceChild(stationIP, iGMASStationNode.namedItem("IPADDRESS"));

    QDomElement stationPort = root.createElement("IPPORT");
    stationPort.appendChild(root.createTextNode(QString::number(station->getPort())));
    iGMASStationNode.replaceChild(stationPort, iGMASStationNode.namedItem("IPPORT"));

    QDomElement stationMount = root.createElement("MOUNT");
    stationMount.appendChild(root.createTextNode(station->getMount()));
    iGMASStationNode.replaceChild(stationMount, iGMASStationNode.namedItem("MOUNT"));

    QDomElement stationMemID = root.createElement("MEMID");
    stationMemID.appendChild(root.createTextNode(QString::number(station->getMemID())));
    iGMASStationNode.replaceChild(stationMemID, iGMASStationNode.namedItem("MEMID"));

    QDomElement stationLongitude = root.createElement("LONGITUDE");
    stationLongitude.appendChild(root.createTextNode(QString::number(station->getLongitude())));
    iGMASStationNode.replaceChild(stationLongitude, iGMASStationNode.namedItem("LONGITUDE"));

    QDomElement stationLatitude = root.createElement("LATITUDE");
    stationLatitude.appendChild(root.createTextNode(QString::number(station->getLatitude())));
    iGMASStationNode.replaceChild(stationLatitude, iGMASStationNode.namedItem("LATITUDE"));

    QDomElement stationHeight = root.createElement("HEIGHT");
    stationHeight.appendChild(root.createTextNode(QString::number(station->getHeight())));
    iGMASStationNode.replaceChild(stationHeight, iGMASStationNode.namedItem("HEIGHT"));

    writeConfigFile();
}

void SMAMTreeWidget::deleteIGMASStation()
{

}

void SMAMTreeWidget::showAddNewIGSStationDialog()
{

}

void SMAMTreeWidget::addNewIGSStation(IGSStation* station)
{
    Q_UNUSED(station);
}

void SMAMTreeWidget::showModifyIGSStationDialog()
{

}

void SMAMTreeWidget::modifyIGSStation(IGSStation* station)
{
    Q_UNUSED(station);
}

void SMAMTreeWidget::deleteIGSStation()
{

}

void SMAMTreeWidget::showAddNewCenterDialog()
{
    AddCenterDialog* dialog = new AddCenterDialog(tree);
    connect(dialog, SIGNAL(confirmButtonClicked(OtherCenter*)), this, SLOT(addNewCenter(OtherCenter*)));
    dialog->show();
}

void SMAMTreeWidget::addNewCenter(OtherCenter* center)
{
    otherCenterList << center;
    tree->currentItem()->addChild(new CenterTreeWidgetItem(tree->currentItem(), CENTERNODE_TREEITEM_TYPE, center));

    QDomElement newCenter = root.createElement("CENTER");

    QDomElement centerName = root.createElement("CENTERNAME");
    centerName.appendChild(root.createTextNode(center->getCenterName()));
    newCenter.appendChild(centerName);

    QDomElement centerIP = root.createElement("IPADDRESS");
    centerIP.appendChild(root.createTextNode(center->getIpAddress()));
    newCenter.appendChild(centerIP);

    QDomElement centerPort = root.createElement("IPPORT");
    centerPort.appendChild(root.createTextNode(QString::number(center->getPort())));
    newCenter.appendChild(centerPort);

    QDomElement centerDetail = root.createElement("DETAIL");
    centerDetail.appendChild(root.createTextNode(center->getDetail()));
    newCenter.appendChild(centerDetail);

    otherCenterRoot.appendChild(newCenter);

    writeConfigFile();
}

void SMAMTreeWidget::showModifyCenterDialog()
{
    ModifyCenterDialog* dialog = new ModifyCenterDialog((OtherCenter*) tree->currentItem()->data(0, Qt::UserRole).value<void*>(), tree);
    connect(dialog, SIGNAL(confirmButtonClicked(OtherCenter*)), this, SLOT(modifyCenter(OtherCenter*)));
    dialog->show();
}

void SMAMTreeWidget::modifyCenter(OtherCenter* center)
{
    addWidgetToContainer(tree->currentItem());

    int index = tree->currentIndex().row();
    QDomNode centerNode = otherCenterRoot.childNodes().at(index);

    QDomElement centerName = root.createElement("CENTERNAME");
    centerName.appendChild(root.createTextNode(center->getCenterName()));
    centerNode.replaceChild(centerName, centerNode.namedItem("CENTERNAME"));

    QDomElement centerIP = root.createElement("IPADDRESS");
    centerIP.appendChild(root.createTextNode(center->getIpAddress()));
    centerNode.replaceChild(centerIP, centerNode.namedItem("IPADDRESS"));

    QDomElement centerPort = root.createElement("IPPORT");
    centerPort.appendChild(root.createTextNode(QString::number(center->getPort())));
    centerNode.replaceChild(centerPort, centerNode.namedItem("IPPORT"));

    QDomElement centerDetail = root.createElement("DETAIL");
    centerDetail.appendChild(root.createTextNode(center->getDetail()));
    centerNode.replaceChild(centerDetail, centerNode.namedItem("DETAIL"));

    writeConfigFile();
}

void SMAMTreeWidget::deleteCenter()
{
    OtherCenter* center = (OtherCenter*) tree->currentItem()->data(0, Qt::UserRole).value<void*>();\
    QString content = tr("确认删除其他中心 ") + center->getCenterName() + tr(" 吗？");
    int ret = QMessageBox::warning(tree,
                                   tr("提示"),
                                   content,
                                   QMessageBox::Cancel | QMessageBox::Ok);
    if (ret == QMessageBox::Ok) {
        otherCenterList.removeAt(tree->currentIndex().row());
        otherCenterRoot.removeChild(otherCenterRoot.childNodes().at(tree->currentIndex().row()));
        delete tree->currentItem()->parent()->takeChild(tree->currentIndex().row());
        writeConfigFile();
    }
}

void SMAMTreeWidget::initAtBJ()
{
    //Get config xml file root
    root = getRootFromXMLFile(BJ_CONFIGFILE_PATH);

    //Create igmas stations root of QTreewidget
    iGMASStationTreeRoot = new QTreeWidgetItem(IGMASROOT_TREEITEM_TYPE);
    iGMASStationTreeRoot->setText(0, tr("iGMAS测站管理"));
    iGMASStationTreeRoot->setIcon(0, QIcon(":/igmas_root"));

    //Read standard stations information from config xml file
    iGMASStationRoot = root.namedItem("BDLSS").namedItem("IGMASSTATIONS");
    if (iGMASStationRoot.isNull()) {
        iGMASStationRoot = root.createElement("IGMASSTATIONS");
        root.namedItem("BDLSS").appendChild(iGMASStationRoot);
    }
    QDomNode iGMASStationNode = iGMASStationRoot.firstChild();
    while (!iGMASStationNode.isNull()) {
        if (iGMASStationNode.isElement()) {
            IGMASStation* station = new IGMASStation();
            station->setIsAvailable(iGMASStationNode.namedItem("ISAVAILABLE").toElement().text());
            station->setIpAddress(iGMASStationNode.namedItem("IPADDRESS").toElement().text());
            station->setPort(iGMASStationNode.namedItem("IPPORT").toElement().text());
            station->setMount(iGMASStationNode.namedItem("MOUNT").toElement().text());
            station->setMemID(iGMASStationNode.namedItem("MEMID").toElement().text());
            station->setLongitude(iGMASStationNode.namedItem("LONGITUDE").toElement().text());
            station->setLatitude(iGMASStationNode.namedItem("LATITUDE").toElement().text());
            station->setHeight(iGMASStationNode.namedItem("HEIGHT").toElement().text());

            //Create station node of QTreewidget
            QTreeWidgetItem* stationTreeNode = new IGMASTreeWidgetItem(iGMASStationTreeRoot, IGMASNODE_TREEITEM_TYPE, station);
            Q_UNUSED(stationTreeNode);
            iGMASStationList << station;
        }
        iGMASStationNode = iGMASStationNode.nextSibling();
    }

    //Create other centers root of QTreewidget
    otherCenterTreeRoot = new QTreeWidgetItem(CENTERROOT_TREEITEM_TYPE);
    otherCenterTreeRoot->setText(0, tr("其他中心管理"));
    otherCenterTreeRoot->setIcon(0, QIcon(":/center_root"));

    //Read other centers information from config xml file
    otherCenterRoot = root.namedItem("BDLSS").namedItem("CENTERS");
    if (otherCenterRoot.isNull()) {
        otherCenterRoot = root.createElement("CENTERS");
        root.namedItem("BDLSS").appendChild(otherCenterRoot);
    }
    QDomNode centerNode = otherCenterRoot.firstChild();
    while (!centerNode.isNull()) {
        if (centerNode.isElement()) {
            OtherCenter* center = new OtherCenter();
            center->setCenterName(centerNode.namedItem("CENTERNAME").toElement().text());
            center->setIpAddress(centerNode.namedItem("IPADDRESS").toElement().text());
            center->setPort(centerNode.namedItem("IPPORT").toElement().text());
            center->setDetail(centerNode.namedItem("DETAIL").toElement().text());

            //Create other center node of QTreewidget
            QTreeWidgetItem* centerTreeNode = new CenterTreeWidgetItem(otherCenterTreeRoot, CENTERNODE_TREEITEM_TYPE, center);
            Q_UNUSED(centerTreeNode);
            otherCenterList << center;
        }
        centerNode = centerNode.nextSibling();
    }

    memoryTreeRoot = new QTreeWidgetItem(MEMINFO_TREEITEM_TYPE);
    memoryTreeRoot->setText(0, tr("内存管理"));
    memoryTreeRoot->setIcon(0, QIcon(":/2"));

    tree->setColumnCount(1);
    tree->addTopLevelItem(iGMASStationTreeRoot);
    tree->addTopLevelItem(otherCenterTreeRoot);
    tree->addTopLevelItem(memoryTreeRoot);
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    iGMASStationTreeRoot->setExpanded(true);
    otherCenterTreeRoot->setExpanded(true);

    //Init shared buffer and write buffer
    if (FindMemoryInfoFunc != 0) {
        void* iGMASStationBufferPointer = FindMemoryInfoFunc(IGMAS_SHAREDBUFFER_ID,
                                                      IGMAS_SHAREDBUFFER_MAXITEMCOUNT * sizeof(IGMASStationInBuffer));

        iGMASStationBuffer = new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                              SharedBuffer::ONLY_WRITE,
                                              iGMASStationBufferPointer,
                                              sizeof(IGMASStationInBuffer));

        void* otherCenterBufferPointer = FindMemoryInfoFunc(OTHERCENTER_SHAREDBUFFER_ID,
                                                            OTHERCENTER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(OtherCenterInBuffer));

        otherCenterBuffer = new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                             SharedBuffer::ONLY_WRITE,
                                             otherCenterBufferPointer,
                                             sizeof(OtherCenterInBuffer));
        writeSharedBuffer();
    }
}

void SMAMTreeWidget::initAtXJ()
{
    //Get config xml file root
    root = getRootFromXMLFile(XJ_CONFIGFILE_PATH);

	//Create standard stations root of QTreewidget
    standardStationTreeRoot = new QTreeWidgetItem(STANDARDROOT_TREEITEM_TYPE);
    standardStationTreeRoot->setText(0, tr("基准站管理"));
    standardStationTreeRoot->setIcon(0, QIcon(":/standard_root"));

    //Read standard stations information from config xml file
    standardStationRoot = root.namedItem("BDLSS").namedItem("STATIONS");
    if (standardStationRoot.isNull()) {
        standardStationRoot = root.createElement("STATIONS");
        root.namedItem("BDLSS").appendChild(standardStationRoot);
    }
    QDomNode stationNode = standardStationRoot.firstChild();
	while (!stationNode.isNull()) {
		if (stationNode.isElement()) {
            StandardStation* station = new StandardStation();
			station->setStationName(stationNode.namedItem("STATIONNAME").toElement().text());
			station->setIpAddress(stationNode.namedItem("IPADDRESS").toElement().text());
			station->setPort(stationNode.namedItem("IPPORT").toElement().text());
			station->setMode(stationNode.namedItem("STATIONMODE").toElement().text());
			station->setServiceThreadCount(stationNode.namedItem("SERVICETHREADCOUNT").toElement().text());
			station->setType(stationNode.namedItem("DEPLOYMENTTYPE").toElement().text());
			station->setDetail(stationNode.namedItem("DETAIL").toElement().text());

			//Create station node of QTreewidget
            QTreeWidgetItem* stationTreeNode = new StandardTreeWidgetItem(standardStationTreeRoot, STANDARDNODE_TREEITEM_TYPE, station);
			standardStationList << station;

			QDomNode receiverNode = stationNode.namedItem("RECEIVERS").firstChild();
			while (!receiverNode.isNull()) {
				if (receiverNode.isElement()) {
                    Receiver* receiver = new Receiver();
					receiver->setReceiverName(receiverNode.namedItem("RECEIVERNAME").toElement().text());
					receiver->setIpAddress(receiverNode.namedItem("IPADDRESS").toElement().text());
					receiver->setPort(receiverNode.namedItem("IPPORT").toElement().text());
					receiver->setLongitude(receiverNode.namedItem("LONGITUDE").toElement().text());
					receiver->setLatitude(receiverNode.namedItem("LATITUDE").toElement().text());
                    receiver->setHeight(receiverNode.namedItem("HEIGHT").toElement().text());
					station->addReceiver(receiver);

					//Create receiver node of QTreewidget
                    QTreeWidgetItem* receiverTreeNode = new ReceiverTreeWidgetItem(stationTreeNode, RECEIVER_TREEITEM_TYPE, receiver);
                    Q_UNUSED(receiverTreeNode);
				}
				receiverNode = receiverNode.nextSibling();
			}
		}
        stationNode = stationNode.nextSibling();
    }

    //Create other centers root of QTreewidget
    otherCenterTreeRoot = new QTreeWidgetItem(CENTERROOT_TREEITEM_TYPE);
    otherCenterTreeRoot->setText(0, tr("其他中心管理"));
    otherCenterTreeRoot->setIcon(0, QIcon(":/center_root"));

    //Read other centers information from config xml file
    otherCenterRoot = root.namedItem("BDLSS").namedItem("CENTERS");
    if (otherCenterRoot.isNull()) {
        otherCenterRoot = root.createElement("CENTERS");
        root.namedItem("BDLSS").appendChild(otherCenterRoot);
    }
    QDomNode centerNode = otherCenterRoot.firstChild();
    while (!centerNode.isNull()) {
        if (centerNode.isElement()) {
            OtherCenter* center = new OtherCenter();
            center->setCenterName(centerNode.namedItem("CENTERNAME").toElement().text());
            center->setIpAddress(centerNode.namedItem("IPADDRESS").toElement().text());
            center->setPort(centerNode.namedItem("IPPORT").toElement().text());
            center->setDetail(centerNode.namedItem("DETAIL").toElement().text());

            //Create other center node of QTreewidget
            QTreeWidgetItem* centerTreeNode = new CenterTreeWidgetItem(otherCenterTreeRoot, CENTERNODE_TREEITEM_TYPE, center);
            Q_UNUSED(centerTreeNode);
            otherCenterList << center;
        }
        centerNode = centerNode.nextSibling();
    }

    memoryTreeRoot = new QTreeWidgetItem(MEMINFO_TREEITEM_TYPE);
    memoryTreeRoot->setText(0, tr("内存管理"));
    memoryTreeRoot->setIcon(0, QIcon(":/2"));

	tree->setColumnCount(1);
    tree->addTopLevelItem(standardStationTreeRoot);
    tree->addTopLevelItem(otherCenterTreeRoot);
    tree->addTopLevelItem(memoryTreeRoot);
	tree->setContextMenuPolicy(Qt::CustomContextMenu);
    standardStationTreeRoot->setExpanded(true);
    otherCenterTreeRoot->setExpanded(true);

    //Init shared buffer and write buffer
    if (FindMemoryInfoFunc != 0) {
        void* standardStationBufferPointer = FindMemoryInfoFunc(STANDARD_SHAREDBUFFER_ID,
                                                 STANDARD_SHAREDBUFFER_MAXITEMCOUNT * sizeof(StandardStationInBuffer));

        standardStationBuffer = new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                          SharedBuffer::ONLY_WRITE,
                                          standardStationBufferPointer,
                                          sizeof(StandardStationInBuffer));

        void* otherCenterBufferPointer = FindMemoryInfoFunc(OTHERCENTER_SHAREDBUFFER_ID,
                                                            OTHERCENTER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(OtherCenterInBuffer));

        otherCenterBuffer = new SharedBuffer(SharedBuffer::COVER_BUFFER,
                                             SharedBuffer::ONLY_WRITE,
                                             otherCenterBufferPointer,
                                             sizeof(OtherCenterInBuffer));
        writeSharedBuffer();
    }
}

QDomDocument SMAMTreeWidget::getRootFromXMLFile(const QString& filePath)
{
	QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly | QFile::Text)) {
        qDebug() << "Configfile " << filePath << " is not existed, create it.";
        if (!configFile.open(QIODevice::ReadWrite | QFile::Text)) {
            qDebug() << "Create configfile " << filePath << " error.";
        }
        else {
            QDomDocument doc;
            QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            doc.appendChild(instruction);
            QDomElement rootElement = doc.createElement("BDLSS");
            doc.appendChild(rootElement);

            QTextStream out(&configFile);
            out.setCodec("UTF-8");
            doc.save(out, 4, QDomNode::EncodingFromTextStream);
            configFile.close();
            return doc;
        }
    }
	QString errorStr;
    int errorLine, errorColumn;
	QDomDocument doc;
	if (!doc.setContent(&configFile, false, &errorStr, &errorLine, &errorColumn)) {
        qDebug()<<"QDomDocument setcontent error, the errormessage is " << errorStr;
    }
	configFile.close();
    return doc;
}

void SMAMTreeWidget::writeConfigFile()
{
    ((MainMonitorWidget*) systemMonitorWidget)->updateView();

    addWidgetToContainer(tree->currentItem());
    writeSharedBuffer();

    QFile file;
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            file.setFileName(XJ_CONFIGFILE_PATH);
            break;
        case DeploymentType::BJ_CENTER:
            file.setFileName(BJ_CONFIGFILE_PATH);
        default:
            break;
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return;
    QTextStream out(&file);
	root.save(out, 2);
    file.close();
}

void SMAMTreeWidget::writeSharedBuffer()
{
    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
        {
            StandardStationInBuffer standard[standardStationList.size()];
            for (int i = 0; i < standardStationList.size(); i++) {
                standard[i] = standardStationList[i]->toStandardStationInBuffer();
            }
            if (standardStationBuffer != 0) {
                standardStationBuffer->writeData(&standard, standardStationList.size());
            }
            OtherCenterInBuffer otherCenter[otherCenterList.size()];
            for (int i = 0; i < otherCenterList.size(); i++) {
                otherCenter[i] = otherCenterList[i]->toOtherCenterInBuffer();
            }
            if (otherCenterBuffer != 0) {
                otherCenterBuffer->writeData(&otherCenter, otherCenterList.size());
            }
            break;
        }
        case DeploymentType::BJ_CENTER:
        {
            IGMASStationInBuffer iGMAS[iGMASStationList.size()];
            for (int i = 0; i < iGMASStationList.size(); i++) {
                iGMAS[i] = iGMASStationList[i]->toiGMASStationInBuffer();
            }
            if (iGMASStationBuffer != 0) {
                iGMASStationBuffer->writeData(&iGMAS, iGMASStationList.size());
            }
            OtherCenterInBuffer otherCenter[otherCenterList.size()];
            for (int i = 0; i < otherCenterList.size(); i++) {
                otherCenter[i] = otherCenterList[i]->toOtherCenterInBuffer();
            }
            if (otherCenterBuffer != 0) {
                otherCenterBuffer->writeData(&otherCenter, otherCenterList.size());
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
