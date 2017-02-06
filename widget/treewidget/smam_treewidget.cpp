#include <QGraphicsScene>
#include <QMessageBox>
#include <QMenu>
#include <QFile>
#include <QDebug>

#include "main_component_header.h"
#include "smam_treewidget.h"
#include "widget/centerinfo_widget.h"
#include "widget/mainmonitor_widget.h"
#include "widget/stationinfo_widget.h"
#include "widget/receiverinfo_widget.h"
#include "widget/sharedmemoryinfo_widget.h"
#include "widget/dialog/add_center_dialog.h"
#include "widget/dialog/modify_center_dialog.h"
#include "widget/dialog/add_receiver_dialog.h"
#include "widget/dialog/modify_receiver_dialog.h"
#include "widget/dialog/add_standardstation_dialog.h"
#include "widget/dialog/modify_standardstation_dialog.h"

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
            break;
    }
    systemMonitorWidget = new MainMonitorWidget(&standardStationList, &otherCenterList);
    currentContentWidget = systemMonitorWidget;
    container->addWidget(currentContentWidget);
}

void SMAMTreeWidget::showRightMenuAtBJ(QPoint pos)
{
    QTreeWidgetItem* curItem = tree->itemAt(pos);
    if (curItem == NULL)
        return;
    QMenu* popMenu =new QMenu;
    switch (curItem->type()) {
        case 00:
        {
            QAction* addNewiGMASStation = new QAction(tr("添加iGMAS站"), this);
            popMenu->addAction(addNewiGMASStation);
            break;
        }
        default:
            break;
    }
    popMenu->exec(QCursor::pos());
}

void SMAMTreeWidget::showRightMenuAtXJ(QPoint pos)
{
	QTreeWidgetItem* curItem = tree->itemAt(pos);
	if (curItem == NULL)
		return;
	QMenu* popMenu =new QMenu;
    switch (curItem->type()) {
        case 00:
        {
            QAction* addNewStandardStation = new QAction(tr("添加基准站"), this);
            connect(addNewStandardStation, SIGNAL(triggered(bool)), this, SLOT(showAddNewStandardStationDialog()));
            popMenu->addAction(addNewStandardStation);
            break;
        }
        case 01:
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
        case 02:
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
        case 10:
        {
            QAction* addNewCenter = new QAction(tr("添加其他中心"), this);
            connect(addNewCenter, SIGNAL(triggered(bool)), this, SLOT(showAddNewCenterDialog()));
            popMenu->addAction(addNewCenter);
            break;
        }
        case 11:
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
        case 00:
        case 10:
            currentContentWidget = systemMonitorWidget;
            break;
		case 01:
			currentContentWidget = new StationInfoWidget();
			((StationInfoWidget*) currentContentWidget)->setStation((StandardStation*) item->data(0, Qt::UserRole).value<void*>());
			break;
		case 02:
			currentContentWidget = new ReceiverInfoWidget();
			((ReceiverInfoWidget*) currentContentWidget)->setReceiver((Receiver*) item->data(0, Qt::UserRole).value<void*>());
			break;
		case 11:
            currentContentWidget = new CenterInfoWidget();
            ((CenterInfoWidget*) currentContentWidget)->setCenter((OtherCenter*) item->data(0, Qt::UserRole).value<void*>());
            break;
        case 20:
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
	tree->currentItem()->addChild(new StandardTreeWidgetItem(tree->currentItem(), station));

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
    if (((StandardStation*) tree->currentItem()->data(0, Qt::UserRole).value<void*>())->getReceivers().size() > MAX_RECEIVER_COUNT_PERSTATION) {
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
	tree->currentItem()->addChild(new ReceiverTreeWidgetItem(tree->currentItem(), receiver));

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

}

void SMAMTreeWidget::addNewIGMASStationDialog(IGMASStation* station)
{

}

void SMAMTreeWidget::showModifyIGMASStationDialog()
{

}

void SMAMTreeWidget::modifyIGMASStation(IGMASStation* station)
{

}

void SMAMTreeWidget::deleteIGMASStation()
{

}

void SMAMTreeWidget::showAddNewIGSStationDialog()
{

}

void SMAMTreeWidget::addNewIGSStationDialog(IGSStation* station)
{

}

void SMAMTreeWidget::showModifyIGSStationDialog()
{

}

void SMAMTreeWidget::modifyIGSStation(IGSStation* station)
{

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
    tree->currentItem()->addChild(new CenterTreeWidgetItem(tree->currentItem(), center));

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
	connect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenuAtBJ(QPoint)));
}

void SMAMTreeWidget::initAtXJ()
{
	//Create standard stations root of QTreewidget
    standardStationTreeRoot = new QTreeWidgetItem(00);
    standardStationTreeRoot->setText(0, tr("基准站管理"));
    standardStationTreeRoot->setIcon(0, QIcon(":/standard_root"));

	//Read info from config xml file
	root = getRootFromXMLFile(STANDARD_CONFIGFILE_PATH);
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
            QTreeWidgetItem* stationTreeNode = new StandardTreeWidgetItem(standardStationTreeRoot, station);
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
					station->addReceiver(receiver);

					//Create receiver node of QTreewidget
					QTreeWidgetItem* receiverTreeNode = new ReceiverTreeWidgetItem(stationTreeNode, receiver);
				}
				receiverNode = receiverNode.nextSibling();
			}
		}
        stationNode = stationNode.nextSibling();
    }

    otherCenterTreeRoot = new QTreeWidgetItem(10);
    otherCenterTreeRoot->setText(0, tr("其他中心管理"));
    otherCenterTreeRoot->setIcon(0, QIcon(":/center_root"));

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

            QTreeWidgetItem* centerTreeNode = new CenterTreeWidgetItem(otherCenterTreeRoot, center);
            otherCenterList << center;
        }
        centerNode = centerNode.nextSibling();
    }

    memoryTreeRoot = new QTreeWidgetItem(20);
    memoryTreeRoot->setText(0, tr("内存管理"));
    memoryTreeRoot->setIcon(0, QIcon(":/2"));

	tree->setColumnCount(1);
    tree->addTopLevelItem(standardStationTreeRoot);
    tree->addTopLevelItem(otherCenterTreeRoot);
    tree->addTopLevelItem(memoryTreeRoot);
	tree->setContextMenuPolicy(Qt::CustomContextMenu);
    standardStationTreeRoot->setExpanded(true);
    otherCenterTreeRoot->setExpanded(true);

	connect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenuAtXJ(QPoint)));
	connect(tree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(addWidgetToContainer(QTreeWidgetItem*)));

    //Init shared buffer and write buffer
    if (FindMemoryInfoFunc != 0) {
        void* bufferPointer = FindMemoryInfoFunc(STANDARD_SHAREDBUFFER_ID, STANDARD_SHAREDBUFFER_MAXITEMCOUNT * sizeof(StandardStationInBuffer));
        standardBuffer = new SharedBuffer(SharedBuffer::COVER_BUFFER, SharedBuffer::ONLY_WRITE, bufferPointer, sizeof(StandardStationInBuffer));
        void* otherCenterBufferPointer = FindMemoryInfoFunc(OTHERCENTER_SHAREDBUFFER_ID, OTHERCENTER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(OtherCenterInBuffer));
        otherCenterBuffer = new SharedBuffer(SharedBuffer::COVER_BUFFER, SharedBuffer::ONLY_WRITE, otherCenterBufferPointer, sizeof(OtherCenterInBuffer));
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
	int errorLine;
	int errorColumn;
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

	QFile file(STANDARD_CONFIGFILE_PATH);
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
            if (standardBuffer != 0) {
                standardBuffer->writeData(&standard, standardStationList.size());
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
            break;
        }
        default:
        {
            break;
        }
    }
}
