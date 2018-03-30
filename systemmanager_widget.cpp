#include <QCloseEvent>
#include <QTime>
#include <QTimer>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QFile>

#include "systemmanager_widget.h"
#include "ui_systemmanager_widget.h"

#include "common.h"
#include "main_component_header.h"
#include "utilities/cpumem_info.h"

extern DeploymentType::Value deploymentType;

extern void* componentStateSharedBufferPointer[COMPONENT_COUNT];
extern void* userRegisterInfoSharedBufferPointer;
extern void* userRealtimeInfoSharedBufferPointer;

SystemManagerWidget::SystemManagerWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SystemManagerWidget)
{
	ui->setupUi(this);
	ui->infoOutputTable->horizontalHeader()->setFixedHeight(TABLEWIDGET_HORIZONHEADER_HEIGHT);
	ui->infoOutputTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->infoOutputTable->verticalHeader()->setVisible(false);
	ui->infoOutputTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->infoOutputTable->setSelectionMode(QAbstractItemView::NoSelection);

    if (deploymentType ==  DeploymentType::BJ_CENTER) {
        ui->totalCountLabel->setText(tr("配置测站数量"));
        ui->onlineCountLabel->setText(tr("正常测站数量"));
    }

    resourceCheckTimer = new QTimer(this);
    connect(resourceCheckTimer, SIGNAL(timeout()), this, SLOT(checkResource()));
    resourceCheckTimer->start(RESOURCE_CHECK_TIMEINTERVAL);

    for (int i = 0; i < COMPONENT_COUNT; i++) {
        messageBuffers[i] = new SharedBuffer(componentStateSharedBufferPointer[i]);
    }
    messageReceiveTimer = new QTimer(this);
    connect(messageReceiveTimer, SIGNAL(timeout()), this, SLOT(checkMessage()));
    messageReceiveTimer->start(MESSAGE_CHECK_TIMEINTERVAL);

    treeWidget = new SMAMTreeWidget(ui->treeWidget, ui->contentContainer);
    softwareStatus = new StatusPushButton(QIcon(":/status_green"), tr("软件运行状态"), this);
    ui->statusContainer->addWidget(softwareStatus);
    ui->diskBar->setMaximum(getTotalDiskSize());
    proc = new QProcess();
    proc->start("top -bd1 -p " + QString::number(getpid()));
}

SystemManagerWidget::~SystemManagerWidget()
{
    delete ui;
}

void SystemManagerWidget::checkResource()
{
    QString result = QString(proc->readAllStandardOutput());
    QStringList lines = result.split(QRegExp("\\n"));
    if (lines.size() >= 10) {
        QStringList array = lines[9].split(QRegExp("\\s+"));
        int startIndex = (array[0] == "") ? 9 : 8;
        ui->cpuBar->setValue(array[startIndex].toDouble() * 10);
        ui->cpuValue->setText(array[startIndex] + "%");
        ui->memBar->setValue(array[startIndex + 1].toDouble() * 10);
        ui->memValue->setText(array[startIndex + 1] + "%");
    }
    ui->diskBar->setValue(getUsedDiskSize());
    ui->diskValue->setText(QString::number(getTotalDiskSize() - getUsedDiskSize()) + "MB");
    ui->dateTimeLabel->setText(QDateTime::currentDateTime().toString(DATETIME_FORMAT_STRING));

    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            ui->totalCount->display(*((int*) userRegisterInfoSharedBufferPointer));
            ui->onlineCount->display(*((int*) userRealtimeInfoSharedBufferPointer));
            break;
        case DeploymentType::BJ_CENTER:
            ui->totalCount->display(ConfigHelper::monitorStations.size());
            int onlineCount = 0;
            for (int i = 0; i < ConfigHelper::monitorStations.size(); i++) {
                if (ConfigHelper::monitorStations[i]->getState() == MonitorStation::NORMAl) {
                    onlineCount++;
                }
            }
            ui->onlineCount->display(onlineCount);
            break;
    }
}

void SystemManagerWidget::checkMessage()
{
    for (int i = 0; i < COMPONENT_COUNT; ++i) {
        while (true) {
            SoftWorkStatus status;
            if (messageBuffers[i]->readData(&status, sizeof(status)) == 0) {
                break;
            }
            int currentRowCount = ui->infoOutputTable->rowCount();
            if (currentRowCount == MESSAGE_MAX_COUNT) {
                ui->infoOutputTable->removeRow(0);
                currentRowCount -= 1;
            }
            ui->infoOutputTable->setRowCount(currentRowCount + 1);
            ui->infoOutputTable->setItem(currentRowCount, 0, new QTableWidgetItem(QDateTime::fromTime_t(status.messageTime).toString(DATETIME_FORMAT_STRING)));
            QString iconName;
            switch (status.messageType) {
                case 1:
                    iconName = ":/info_normal";
                    break;
                case 2:
                    iconName = ":/info_warning";
                    break;
                case 3:
                    iconName = ":/info_error";
                    break;
                default:
                    iconName = ":/info_normal";
                    break;
            }
            ui->infoOutputTable->setItem(currentRowCount, 1, new QTableWidgetItem(QIcon(iconName), QString(status.messageContent)));
            ui->infoOutputTable->setRowHeight(currentRowCount, 22);
            ui->infoOutputTable->setCurrentCell(currentRowCount, 0);
        }
    }
}

void SystemManagerWidget::changeOnlineStationCount(bool isOnline)
{
    ui->onlineCount->display(ui->onlineCount->value() + (isOnline ? 1 : -1));
}

void SystemManagerWidget::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    emit closeMessage();
}
