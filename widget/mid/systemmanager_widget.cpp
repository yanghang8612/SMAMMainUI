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

    startTimer(500);
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
    proc->start("top -bd1 -p " + QString::number(getpid()));
}

SystemManagerWidget::~SystemManagerWidget()
{
	delete ui;
}

void SystemManagerWidget::timerEvent(QTimerEvent*)
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
	QDateTime time = QDateTime::currentDateTime();
	ui->dateLabel->setText(time.toString(DATE_FORMAT_STRING));
    ui->timeLabel->setText(time.toString(TIME_FORMAT_STRING));

    if (userRegisterInfoSharedBufferPointer != 0) {
        ui->registeredUserCount->display(*((int*) userRegisterInfoSharedBufferPointer));
    }
    if (userRealtimeInfoSharedBufferPointer != 0) {
        ui->onlineUserCount->display(*((int*) userRealtimeInfoSharedBufferPointer));
    }
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
            if (currentRowCount == MESSAGE_MAX_COUNT) {
                ui->infoOutputTable->removeColumn(0);
                currentRowCount -= 1;
            }
            else {
                ui->infoOutputTable->setRowCount(currentRowCount + 1);
            }
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

void SystemManagerWidget::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    emit closeMessage();
}
