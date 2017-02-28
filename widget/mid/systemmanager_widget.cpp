﻿#include <QCloseEvent>
#include <QTime>
#include <QTimer>
#include <QDebug>

#include "systemmanager_widget.h"
#include "ui_systemmanager_widget.h"
#include "common.h"
#include "main_component_header.h"
#include "library_exportfunction.h"

FINDMEMORYINFOFUNC FindMemoryInfoFunc = 0;
DLLSTATUSREADFUNC  DllStatusReadFunc = 0;
DLLSTATUSWRITEFUNC DllStatusWriteFunc = 0;
SOFTWORKSTATUSWRITEFUNC SoftWorkStatusWriteFunc = 0;

DeploymentType::Value deploymentType;

SystemManagerWidget::SystemManagerWidget(DeploymentType::Value type, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SystemManagerWidget)
{
    qDebug() << sizeof(IGMASStationInBuffer);
    deploymentType = type;
	ui->setupUi(this);
	ui->infoOutputTable->horizontalHeader()->setFixedHeight(TABLEWIDGET_HORIZONHEADER_HEIGHT);
	ui->infoOutputTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->infoOutputTable->verticalHeader()->setVisible(false);
	ui->infoOutputTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->infoOutputTable->setSelectionMode(QAbstractItemView::NoSelection);

	timerID = startTimer(1000);
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    if (FindMemoryInfoFunc != 0) {
        for (int i = 0; i < COMPONENT_COUNT; i++) {
            messageBuffers[i] = new SharedBuffer(SharedBuffer::LOOP_BUFFER, SharedBuffer::ONLY_READ, FindMemoryInfoFunc(i + 2, 0));
        }
    }
    else {
        for (int i = 0; i < COMPONENT_COUNT; i++) {
            messageBuffers[i] = 0;
        }
    }
    QTimer* messageReceiverTimer = new QTimer(this);
    connect(messageReceiverTimer, SIGNAL(timeout()), this, SLOT(addMessageToInfoContainer()));
    messageReceiverTimer->start(MESSAGE_CHECK_TIMEINTERVAL);

    treeWidget = new SMAMTreeWidget(ui->treeWidget, ui->contentContainer);

    softwareStatus = new StatusPushButton(QIcon(":/status_green"), tr("软件运行状态"), this);
    ui->statusContainer->addWidget(softwareStatus);
}

SystemManagerWidget::~SystemManagerWidget()
{
    killTimer(timerID);
	delete ui;
}

void SystemManagerWidget::timerEvent(QTimerEvent*)
{
//    ui->cpuBar->setValue((int) (get_pcpu(getpid()) * 100));
//    ui->memoryBar->setValue((int) (get_pmem(getpid()) * 100));
	ui->onlineUserCount->display(ui->onlineUserCount->intValue() + (qrand() % 10 - 5));

	QDateTime time = QDateTime::currentDateTime();
	ui->dateLabel->setText(time.toString(DATE_FORMAT_STRING));
	ui->timeLabel->setText(time.toString(TIME_FORMAT_STRING));
}

void SystemManagerWidget::addMessageToInfoContainer()
{
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
