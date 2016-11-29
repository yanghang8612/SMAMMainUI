#include <QtGlobal>
#include <QTime>
#include <QTimer>

#include "systemmanager_widget.h"
#include "ui_systemmanager_widget.h"
#include "common.h"

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

	timerID = startTimer(1000);
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(addMessageToInfoContainer()));
	timer->start(2000);

	treeWidget = new SMAMTreeWidget(ui->treeWidget, ui->contentContainer, DeploymentType::XJ_CENTER);

	softwareStatus = new StatusPushButton(QIcon(":/status_red"), tr("软件运行状态"), this);
	otherCentreStatus = new StatusPushButton(QIcon(":/status_green"), tr("其他中心状态"), this);
	ui->statusContainer->addWidget(softwareStatus);
	ui->statusContainer->addWidget(otherCentreStatus);
}

SystemManagerWidget::~SystemManagerWidget()
{
	killTimer(timerID);
	delete ui;
}

void SystemManagerWidget::timerEvent(QTimerEvent*)
{
	ui->cpuBar->setValue((int) (get_pcpu(getpid()) * 100));
	ui->memoryBar->setValue((int) (get_pmem(getpid()) * 100));
	ui->onlineUserCount->display(ui->onlineUserCount->intValue() + (qrand() % 10 - 5));

	QDateTime time = QDateTime::currentDateTime();
	ui->dateLabel->setText(time.toString(DATE_FORMAT_STRING));
	ui->timeLabel->setText(time.toString(TIME_FORMAT_STRING));
}

void SystemManagerWidget::addMessageToInfoContainer()
{
	int type = qrand() % 10;
	int currentRowCount = ui->infoOutputTable->rowCount();
	ui->infoOutputTable->setRowCount(currentRowCount + 1);
	ui->infoOutputTable->setItem(currentRowCount, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString(DATETIME_FORMAT_STRING)));
	if (type < 7) {
		ui->infoOutputTable->setItem(currentRowCount, 1, new QTableWidgetItem(QIcon(":/info_normal"), tr("这是一条正常的消息")));
	}
	else if (type < 9) {
		ui->infoOutputTable->setItem(currentRowCount, 1, new QTableWidgetItem(QIcon(":/info_warning"), tr("这是一条异常的消息")));
	}
	else {
		ui->infoOutputTable->setItem(currentRowCount, 1, new QTableWidgetItem(QIcon(":/info_error"), tr("这是一条错误的消息")));
	}
	ui->infoOutputTable->setRowHeight(currentRowCount, 22);
	ui->infoOutputTable->setCurrentCell(currentRowCount, 0);
}
