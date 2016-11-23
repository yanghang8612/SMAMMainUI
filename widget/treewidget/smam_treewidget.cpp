#include <typeinfo>
#include <QMenu>

#include "smam_treewidget.h"

SMAMTreeWidget::SMAMTreeWidget(QTreeWidget* tree, DeploymentType::Value type) :
	tree(tree), type(type)
{
	if (DeploymentType::XJ_CENTER == type) {
		initAtXJ();
	}
	else if (DeploymentType::BJ_CENTER == type) {
		initAtBJ();
	}
}

void SMAMTreeWidget::showRightMenuAtBJ(QPoint pos)
{

}

void SMAMTreeWidget::showRightMenuAtXJ(QPoint pos)
{
	QTreeWidgetItem* curItem = tree->itemAt(pos);
	if(curItem == NULL)
		return;
	if(curItem->type() == 1)
	{
	   QMenu* popMenu =new QMenu;

	   QAction* addNewReceiver = new QAction(tr("添加接收机"), this);
	   popMenu->addAction(addNewReceiver);
	   QAction* configStation = new QAction(tr("编辑基准站"), this);
	   popMenu->addAction(configStation);
	   QAction* removeStation = new QAction(tr("删除基准站"), this);
	   popMenu->addAction(removeStation);
	   popMenu->exec(QCursor::pos());
	}
	else if(curItem->type() == 2)
	{
	   QMenu* popMenu =new QMenu;

	   QAction* startReceiver = new QAction(tr("启动接收机"), this);
	   popMenu->addAction(startReceiver);
	   QAction* stopReceiver = new QAction(tr("停止接收机"), this);
	   popMenu->addAction(stopReceiver);
	   QAction* configReceiver = new QAction(tr("编辑接收机"), this);
	   popMenu->addAction(configReceiver);
	   QAction* removeReceiver = new QAction(tr("删除接收机"), this);
	   popMenu->addAction(removeReceiver);
	   popMenu->exec(QCursor::pos());
	}
}

void SMAMTreeWidget::initAtBJ()
{
	connect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenuAtBJ(QPoint)));
}

void SMAMTreeWidget::initAtXJ()
{
	//Create standard stations root of QTreewidget
	QTreeWidgetItem* stationRoot = new QTreeWidgetItem(0);
	stationRoot->setText(0, tr("基准站管理"));

	//Read info from config xml file
	QDomElement rootElement = getRootFromXMLFile(STANDARD_CONFIGFILE_PATH);
	QDomNode stationNode = rootElement.firstChild();
	while (!stationNode.isNull()) {
		if(stationNode.isElement()) {
			StandardStation* station = new StandardStation;
			QDomElement stationElement = stationNode.toElement();
			QDomNodeList stationProperties = stationElement.childNodes();
			station->setStationName(stationProperties.at(0).toElement().text());
			station->setIpAddress(stationProperties.at(1).toElement().text());
			station->setPort(stationProperties.at(2).toElement().text());
			station->setMode(stationProperties.at(3).toElement().text());
			station->setServiceThreadCount(stationProperties.at(4).toElement().text());
			station->setType(stationProperties.at(5).toElement().text());
			station->setDetail(stationProperties.at(6).toElement().text());

			//Create station node of QTreewidget

			QTreeWidgetItem* stationNode = new StandardTreeWidgetItem(station, stationRoot);
			stationRoot->addChild(stationNode);

			QDomElement receiversElement = stationProperties.at(7).toElement();
			QDomNode receiverNode = receiversElement.firstChild();
			while (!receiverNode.isNull()) {
				if (receiverNode.isElement()) {
					Receiver* receiver = new Receiver;
					QDomElement receiverElement = receiverNode.toElement();
					QDomNodeList receiverProperties = receiverElement.childNodes();
					receiver->setReceiverName(receiverProperties.at(0).toElement().text());
					receiver->setIpAddress(receiverProperties.at(1).toElement().text());
					receiver->setPort(receiverProperties.at(2).toElement().text());
					receiver->setLongitude(receiverProperties.at(3).toElement().text());
					receiver->setLatitude(receiverProperties.at(4).toElement().text());
					station->addReceiver(receiver);

					//Create receiver node of QTreewidget
					QTreeWidgetItem* receiverNode = new ReceiverTreeWidgetItem(receiver, stationNode);
				}
				receiverNode = receiverNode.nextSibling();
			}
			standardStations << station;
		}
		stationNode = stationNode.nextSibling();
	}

	tree->setColumnCount(1);
	tree->addTopLevelItem(stationRoot);

	tree->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenuAtXJ(QPoint)));
}

QDomElement SMAMTreeWidget::getRootFromXMLFile(const QString& filePath)
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
	return doc.documentElement();
}
