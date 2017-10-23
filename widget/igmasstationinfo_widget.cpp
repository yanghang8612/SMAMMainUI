#include <QMenu>
#include <QMessageBox>
#include <QDebug>

#include "igmasstationinfo_widget.h"
#include "ui_igmasstationinfo_widget.h"

#include "main_component_header.h"
#include "utilities/config_helper.h"
#include "dialog/igmasdatacenter_select_dialog.h"

iGMASStationInfoWidget::iGMASStationInfoWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::iGMASStationInfoWidget)
{
    ui->setupUi(this);
    connect(ui->dataCenterList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenu(QPoint)));
    connect(ui->dataCenterList, SIGNAL(dragCompleted()), this, SLOT(handleDragAction()));

    registerSignalSender(this);
}

iGMASStationInfoWidget::~iGMASStationInfoWidget()
{
    delete ui;
}

void iGMASStationInfoWidget::setStation(iGMASStation* station)
{
    this->station = station;
    ui->stationNameEdit->setText(station->getStationName());
    ui->mountPointEdit->setText(station->getMountPoint());
    ui->longitudeEdit->setText(QString::number(station->getLongitude()));
    ui->latitudeEdit->setText(QString::number(station->getLatitude()));
    ui->heightEdit->setText(QString::number(station->getHeight()));
    ui->detailEdit->setText(station->getDetail());

    dataCenters = station->getDataCenters().split(",", QString::SkipEmptyParts);
    for (int i = 0; i < dataCenters.size(); i++) {
        QListWidgetItem* listItem = new QListWidgetItem(
                                        QIcon(":/datacenter"),
                                        ConfigHelper::getIGMASDataCenterByCenterID(dataCenters[i].toUInt())->getCenterName());
        listItem->setData(Qt::UserRole, QVariant(dataCenters[i]));
        ui->dataCenterList->addItem(listItem);
    }
}

void iGMASStationInfoWidget::showRightMenu(QPoint pos)
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

void iGMASStationInfoWidget::showAddDataCenterDialog()
{
    if (dataCenters.size() != ConfigHelper::iGMASDataCenters.size()) {
        iGMASDataCenterSelectDialog* dialog = new iGMASDataCenterSelectDialog(station->getDataCenters(), this);
        connect(dialog, SIGNAL(confirmButtonClicked(QString)), this, SLOT(addDataCenter(QString)));
        dialog->show();
    }
}

void iGMASStationInfoWidget::addDataCenter(const QString& newDataCenters)
{
    QStringList newDataCenterList = newDataCenters.split(",", QString::SkipEmptyParts);
    for (int i = 0; i < newDataCenterList.size(); i++) {
        QListWidgetItem* listItem = new QListWidgetItem(
                                        QIcon(":/datacenter"),
                                        ConfigHelper::getIGMASDataCenterByCenterID(newDataCenterList[i].toUInt())->getCenterName());
        listItem->setData(Qt::UserRole, QVariant(newDataCenterList[i]));
        ui->dataCenterList->addItem(listItem);
    }
    station->setDataCenters(station->getDataCenters() + newDataCenters);
    ConfigHelper::update();
    emit dataSourceModified(station->getMemID());
}

void iGMASStationInfoWidget::deleteDataCenter()
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

void iGMASStationInfoWidget::handleDragAction()
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
