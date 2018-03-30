#include <QMenu>
#include <QMessageBox>
#include <QDebug>

#include "monitorstationinfo_widget.h"
#include "ui_monitorstationinfo_widget.h"

#include "main_component_header.h"
#include "utilities/config_helper.h"
#include "utilities/general_functions.h"
#include "dialog/datacenter_select_dialog.h"

MonitorStationInfoWidget::MonitorStationInfoWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::MonitorStationInfoWidget)
{
    ui->setupUi(this);
    this->hide();
    connect(ui->dataCenterList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenu(QPoint)));
    connect(ui->dataCenterList, SIGNAL(dragCompleted()), this, SLOT(handleDragAction()));

    registerSignalSender(this);
}

MonitorStationInfoWidget::~MonitorStationInfoWidget()
{
    delete ui;
    removeSignalSender(this);
}

void MonitorStationInfoWidget::setStation(MonitorStation* station)
{
    this->station = station;
    ui->stationNameEdit->setText(station->getStationName());
    ui->mountPointEdit->setText(station->getMountPoint());
    ui->longitudeEdit->setText(GeneralFunctions::convertDMSToQString(station->getLongitude()));
    ui->latitudeEdit->setText(GeneralFunctions::convertDMSToQString(station->getLatitude()));
    ui->heightEdit->setText(QString::number(station->getHeight()));
    ui->detailEdit->setText(station->getDetail());
    ui->dataCenterList->clear();
    dataCenters = station->getDataCenters().split(",", QString::SkipEmptyParts);
    for (int i = 0; i < dataCenters.size(); i++) {
        QListWidgetItem* listItem = new QListWidgetItem(
                                        QIcon(":/datacenter"),
                                        ConfigHelper::getDataCenterByCenterID(dataCenters[i].toUInt())->getCenterName());
        listItem->setData(Qt::UserRole, QVariant(dataCenters[i]));
        ui->dataCenterList->addItem(listItem);
    }
}

void MonitorStationInfoWidget::showRightMenu(QPoint pos)
{
    QMenu* popMenu =new QMenu;
    QAction* addDataCenter = new QAction(tr("添加数据源"), this);
    connect(addDataCenter, SIGNAL(triggered(bool)), this, SLOT(showAddDataCenterDialog()));
    popMenu->addAction(addDataCenter);
    if (ui->dataCenterList->itemAt(pos) != 0) {
        QAction* deleteDataCenter = new QAction(tr("移除数据源"), this);
        connect(deleteDataCenter, SIGNAL(triggered(bool)), this, SLOT(deleteDataCenter()));
        popMenu->addAction(deleteDataCenter);
    }
    popMenu->exec(QCursor::pos());
}

void MonitorStationInfoWidget::showAddDataCenterDialog()
{
    if (dataCenters.size() != ConfigHelper::dataCenters.size()) {
        DataCenterSelectDialog* dialog = new DataCenterSelectDialog(station->getDataCenters(), this);
        connect(dialog, SIGNAL(confirmButtonClicked(QString)), this, SLOT(addDataCenter(QString)));
        dialog->show();
    }
}

void MonitorStationInfoWidget::addDataCenter(const QString& newDataCenters)
{
    QStringList newDataCenterList = newDataCenters.split(",", QString::SkipEmptyParts);
    for (int i = 0; i < newDataCenterList.size(); i++) {
        QListWidgetItem* listItem = new QListWidgetItem(
                                        QIcon(":/datacenter"),
                                        ConfigHelper::getDataCenterByCenterID(newDataCenterList[i].toUInt())->getCenterName());
        listItem->setData(Qt::UserRole, QVariant(newDataCenterList[i]));
        ui->dataCenterList->addItem(listItem);
    }
    station->setDataCenters(station->getDataCenters() + newDataCenters);
    ConfigHelper::update();
    emit dataSourceModified(station->getMemID());
}

void MonitorStationInfoWidget::deleteDataCenter()
{
    int index = ui->dataCenterList->currentIndex().row();
    dataCenters.removeAt(index);
    QString newDataCenters = "";
    for (int i = 0; i < dataCenters.size(); i++) {
        newDataCenters += (dataCenters[i] + ",");
    }
    station->setDataCenters(newDataCenters);
    ConfigHelper::update();
    emit dataSourceDeleted(station->getMemID(), index);
    delete ui->dataCenterList->takeItem(index);
}

void MonitorStationInfoWidget::handleDragAction()
{
    dataCenters.clear();
    QString newDataCenters = "";
    for (int i = 0; i < ui->dataCenterList->count(); i++) {
        dataCenters.append(ui->dataCenterList->item(i)->data(Qt::UserRole).toString());
        newDataCenters += (ui->dataCenterList->item(i)->data(Qt::UserRole).toString() + ",");
    }
    station->setDataCenters(newDataCenters);
    ConfigHelper::update();
    emit dataSourceModified(station->getMemID());
}
