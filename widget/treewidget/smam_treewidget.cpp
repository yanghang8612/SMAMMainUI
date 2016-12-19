#include <QMenu>

#include "smam_treewidget.h"
#include "widget/stationinfo_widget.h"
#include "widget/receiverinfo_widget.h"
#include "widget/usermanager_widget.h"
#include "widget/useronline_widget.h"
#include "widget/mainmonitor_widget.h"
#include "dialog/add_standardstation_dialog.h"
#include "dialog/modify_standardstation_dialog.h"
#include "dialog/add_receiver_dialog.h"
#include "dialog/modify_receiver_dialog.h"

SMAMTreeWidget::SMAMTreeWidget(QTreeWidget* tree, QVBoxLayout* container, DeploymentType::Value type) :
	tree(tree), container(container), type(type),
    currentContentWidget(0)
{
	if (DeploymentType::XJ_CENTER == type) {
		initAtXJ();
	}
	else if (DeploymentType::BJ_CENTER == type) {
		initAtBJ();
	}
    systemMonitorWidget = new MainMonitorWidget(&standardStationList);
    currentContentWidget = systemMonitorWidget;
    container->addWidget(currentContentWidget);
}

void SMAMTreeWidget::showRightMenuAtBJ(QPoint pos)
{
	Q_UNUSED(pos)
}

void SMAMTreeWidget::showRightMenuAtXJ(QPoint pos)
{
	QTreeWidgetItem* curItem = tree->itemAt(pos);
	if (curItem == NULL)
		return;
	QMenu* popMenu =new QMenu;
	if (curItem->type() == 0)
	{
	   QAction* addNewStandardStation = new QAction(tr("添加基准站"), this);
	   connect(addNewStandardStation, SIGNAL(triggered(bool)), this, SLOT(showAddNewStandardStationDialog()));
	   popMenu->addAction(addNewStandardStation);

	}
	else if (curItem->type() == 1)
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
	}
	else if (curItem->type() == 2)
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
			currentContentWidget = new UserManagerWidget();
			break;
		case 12:
			currentContentWidget = new UserOnlineWidget();
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
		container->addWidget(new QWidget);
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
	stationType.appendChild(root.createTextNode(QString::number((int) type)));
	newStandardStation.appendChild(stationType);

	QDomElement stationDetail = root.createElement("DETAIL");
	stationDetail.appendChild(root.createTextNode(station->getDetail()));
	newStandardStation.appendChild(stationDetail);

	QDomElement receiverList = root.createElement("RECEIVERS");
	newStandardStation.appendChild(receiverList);

	root.namedItem("STATIONS").appendChild(newStandardStation);

	writeConfigFile();
}

void SMAMTreeWidget::showModifyStandardStationDialog()
{
	ModifyStandardStationDialog* dialog = new ModifyStandardStationDialog(tree,
											  (StandardStation*) tree->currentItem()->data(0, Qt::UserRole).value<void*>());
	connect(dialog, SIGNAL(confirmButtonClicked(StandardStation*)), this, SLOT(modifyStandardStation(StandardStation*)));
	dialog->show();
}

void SMAMTreeWidget::modifyStandardStation(StandardStation* station)
{
	addWidgetToContainer(tree->currentItem());

	int index = tree->currentIndex().row();
	QDomNode standardStationNode = root.namedItem("STATIONS").childNodes().at(index);

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
	stationType.appendChild(root.createTextNode(QString::number((int) type)));
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
		root.namedItem("STATIONS").removeChild(root.namedItem("STATIONS").childNodes().at(tree->currentIndex().row()));
		delete tree->currentItem()->parent()->takeChild(tree->currentIndex().row());
		writeConfigFile();
	}
}

void SMAMTreeWidget::showAddNewReceiverDialog()
{
	AddReceiverDialog* dialog = new AddReceiverDialog(tree);
	connect(dialog, SIGNAL(confirmButtonClicked(Receiver*)), this, SLOT(addNewReceiver(Receiver*)));
	dialog->show();
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

	root.namedItem("STATIONS").childNodes().at(tree->currentIndex().row()).namedItem("RECEIVERS").appendChild(newReceiver);

	writeConfigFile();
}

void SMAMTreeWidget::showModifyReceiverDialog()
{
	ModifyReceiverDialog* dialog = new ModifyReceiverDialog(tree,
											  (Receiver*) tree->currentItem()->data(0, Qt::UserRole).value<void*>());
	connect(dialog, SIGNAL(confirmButtonClicked(Receiver*)), this, SLOT(modifyReceiver(Receiver*)));
	dialog->show();
}

void SMAMTreeWidget::modifyReceiver(Receiver* receiver)
{
	addWidgetToContainer(tree->currentItem());

	int parentNodeIndex = stationTreeRoot->indexOfChild(tree->currentItem()->parent());
	int nodeIndex = tree->currentIndex().row();
	QDomNode receiverNode = root.namedItem("STATIONS").childNodes().at(parentNodeIndex).namedItem("RECEIVERS").childNodes().at(nodeIndex);

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
		int parentNodeIndex = stationTreeRoot->indexOfChild(tree->currentItem()->parent());
        standardStationList.at(parentNodeIndex)->removerReceiver(tree->currentIndex().row());
		QDomNode parentNode = root.namedItem("STATIONS").childNodes().at(parentNodeIndex).namedItem("RECEIVERS");
		parentNode.removeChild(parentNode.childNodes().at(tree->currentIndex().row()));
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
	stationTreeRoot = new QTreeWidgetItem(00);
	stationTreeRoot->setText(0, tr("基准站管理"));
	stationTreeRoot->setIcon(0, QIcon(":/standard_root"));

	//Read info from config xml file
	root = getRootFromXMLFile(STANDARD_CONFIGFILE_PATH);
	QDomNode stationNode = root.namedItem("STATIONS").firstChild();
	while (!stationNode.isNull()) {
		if (stationNode.isElement()) {
			StandardStation* station = new StandardStation;
			station->setStationName(stationNode.namedItem("STATIONNAME").toElement().text());
			station->setIpAddress(stationNode.namedItem("IPADDRESS").toElement().text());
			station->setPort(stationNode.namedItem("IPPORT").toElement().text());
			station->setMode(stationNode.namedItem("STATIONMODE").toElement().text());
			station->setServiceThreadCount(stationNode.namedItem("SERVICETHREADCOUNT").toElement().text());
			station->setType(stationNode.namedItem("DEPLOYMENTTYPE").toElement().text());
			station->setDetail(stationNode.namedItem("DETAIL").toElement().text());

			//Create station node of QTreewidget
			QTreeWidgetItem* stationTreeNode = new StandardTreeWidgetItem(stationTreeRoot, station);
			standardStationList << station;

			QDomNode receiverNode = stationNode.namedItem("RECEIVERS").firstChild();
			while (!receiverNode.isNull()) {
				if (receiverNode.isElement()) {
					Receiver* receiver = new Receiver;
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

	//Create user root of QTreeWidget
	userTreeRoot = new QTreeWidgetItem(10);
	userTreeRoot->setText(0, tr("终端用户"));
	userTreeRoot->setIcon(0, QIcon(":/user_root"));

	QTreeWidgetItem* userManager = new QTreeWidgetItem(userTreeRoot, 11);
	userManager->setText(0, tr("用户管理"));
	userManager->setIcon(0, QIcon(":/user_manager"));

	QTreeWidgetItem* userOnline = new QTreeWidgetItem(userTreeRoot, 12);
	userOnline->setText(0 ,tr("在线用户"));
	userOnline->setIcon(0, QIcon(":/user_online"));

	tree->setColumnCount(1);
	tree->addTopLevelItem(stationTreeRoot);
	tree->addTopLevelItem(userTreeRoot);
	tree->setContextMenuPolicy(Qt::CustomContextMenu);
	stationTreeRoot->setExpanded(true);
	userTreeRoot->setExpanded(true);

	connect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenuAtXJ(QPoint)));
	connect(tree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(addWidgetToContainer(QTreeWidgetItem*)));
}

QDomDocument SMAMTreeWidget::getRootFromXMLFile(const QString& filePath)
{
	QFile configFile(filePath);
	if (!configFile.open(QIODevice::ReadWrite | QFile::Text)) {
		qDebug() << "open configfile error:" << filePath;
	}
	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomDocument doc;
	if (!doc.setContent(&configFile, false, &errorStr, &errorLine, &errorColumn)) {
		qDebug()<<"setcontent error." ;
		configFile.close();
	}
	configFile.close();
	return doc;
}

void SMAMTreeWidget::writeConfigFile()
{
    ((MainMonitorWidget*) systemMonitorWidget)->updateView();

    addWidgetToContainer(tree->currentItem());

	QFile file(STANDARD_CONFIGFILE_PATH);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return;
	QTextStream out(&file);
	root.save(out, 2);
	file.close();
}
