#include <QCloseEvent>
#include <QTime>
#include <QTimer>
#include <QStringList>
#include <QDebug>

#include "systemmanager_widget.h"
#include "ui_systemmanager_widget.h"

#include "common.h"
#include "main_component_header.h"
#include "utilies/cpumem_info.h"

FINDMEMORYINFOFUNC FindMemoryInfoFunc = 0;
DLLSTATUSREADFUNC  DllStatusReadFunc = 0;
DLLSTATUSWRITEFUNC DllStatusWriteFunc = 0;
SOFTWORKSTATUSWRITEFUNC SoftWorkStatusWriteFunc = 0;

DeploymentType::Value deploymentType;

extern void* componentStateSharedBufferPointer[COMPONENT_COUNT];
extern void* userRegisterInfoSharedBufferPointer;
extern void* userRealtimeInfoSharedBufferPointer;

SystemManagerWidget::SystemManagerWidget(DeploymentType::Value type, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SystemManagerWidget)
{   
	ui->setupUi(this);
	ui->infoOutputTable->horizontalHeader()->setFixedHeight(TABLEWIDGET_HORIZONHEADER_HEIGHT);
	ui->infoOutputTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->infoOutputTable->verticalHeader()->setVisible(false);
	ui->infoOutputTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->infoOutputTable->setSelectionMode(QAbstractItemView::NoSelection);

    deploymentType = type;
    for (int i = 0; i < COMPONENT_COUNT; i++) {
        messageBuffers[i] = 0;
    }

    startTimer(1000);
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QTimer* messageReceiverTimer = new QTimer(this);
    connect(messageReceiverTimer, SIGNAL(timeout()), this, SLOT(addMessageToInfoContainer()));
    messageReceiverTimer->start(MESSAGE_CHECK_TIMEINTERVAL);

    treeWidget = new SMAMTreeWidget(ui->treeWidget, ui->contentContainer);
    softwareStatus = new StatusPushButton(treeWidget->getComponentStateCheckIntervals(), QIcon(":/status_green"), tr("软件运行状态"), this);
    connect(softwareStatus, SIGNAL(componentStateCheckIntervalsChanged()), treeWidget, SLOT(updateComponentStateCheckIntervals()));
    ui->statusContainer->addWidget(softwareStatus);
    ui->diskBar->setMaximum(getTotalDiskSize());
    proc = new QProcess();
    QStringList options;
    options << "-c";
    options << "top -bn1 | grep " + QString::number(getpid());
    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(dataReady()));
    //proc->start("/bin/bash -c \"top -bn1 | grep " + QString::number(getpid()) + "\"");
}

SystemManagerWidget::~SystemManagerWidget()
{
	delete ui;
}

void SystemManagerWidget::timerEvent(QTimerEvent*)
{
    proc->start("/bin/bash -c \"top -bn1 | grep " + QString::number(getpid()) + "\"");
    //proc->kill();
//    ui->cpuBar->setValue((int) (get_pcpu(getpid()) * 100));
//    ui->memoryBar->setValue((int) (get_pmem(getpid()) * 100));
    ui->diskBar->setValue(getUsedDiskSize());

	QDateTime time = QDateTime::currentDateTime();
	ui->dateLabel->setText(time.toString(DATE_FORMAT_STRING));
    ui->timeLabel->setText(time.toString(TIME_FORMAT_STRING));

//    if (deploymentType == DeploymentType::XJ_CENTER) {
        if (userRegisterInfoSharedBufferPointer != 0) {
            ui->registeredUserCount->display(*((int*) userRegisterInfoSharedBufferPointer));
        }
        if (userRealtimeInfoSharedBufferPointer != 0) {
            ui->onlineUserCount->display(*((int*) userRealtimeInfoSharedBufferPointer));
        }
        //    }
}

void SystemManagerWidget::dataReady()
{
    QString result = QString(proc->readAllStandardOutput());
    QStringList array = result.split(QRegExp("\\s+"));
    ui->cpuBar->setValue(array.at(9).toDouble() * 10.0);
    ui->cpuValue->setText(array.at(9) + "%");
    ui->memBar->setValue(array.at(10).toDouble() * 10.0);
    ui->memValue->setText(array.at(10) + "%");
}

void SystemManagerWidget::addMessageToInfoContainer()
{
    for (int i = 0; i < COMPONENT_COUNT; i++) {
        if (messageBuffers[i] == 0) {
            messageBuffers[i] = (componentStateSharedBufferPointer[i] == 0) ? 0 : new SharedBuffer(SharedBuffer::LOOP_BUFFER,
                                                                                                   SharedBuffer::ONLY_READ,
                                                                                                   componentStateSharedBufferPointer[i]);
        }
    }
	int currentRowCount = ui->infoOutputTable->rowCount();
    for (int i = 0; i < 6; ++i) {
        while (true) {
            SoftWorkStatus status;
            if (messageBuffers[i] == 0 || messageBuffers[i]->readData(&status, sizeof(status)) == 0) {
                break;
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
                    break;
            }
            ui->infoOutputTable->setItem(currentRowCount, 1, new QTableWidgetItem(QIcon(iconName), QString(status.messageContent)));
            ui->infoOutputTable->setRowHeight(currentRowCount, 22);
            ui->infoOutputTable->setCurrentCell(currentRowCount, 0);
            currentRowCount++;
        }
    }
}

void SystemManagerWidget::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    emit closeMessage();
}
