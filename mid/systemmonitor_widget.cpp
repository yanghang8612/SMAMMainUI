#include "systemmonitor_widget.h"
#include "ui_systemmonitor_widget.h"

SystemMonitorWidget::SystemMonitorWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SystemMonitorWidget)
{
	ui->setupUi(this);
}

SystemMonitorWidget::~SystemMonitorWidget()
{
	delete ui;
}
