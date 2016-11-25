#include "systemmanager_widget.h"
#include "ui_systemmanager_widget.h"

SystemManagerWidget::SystemManagerWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SystemManagerWidget)
{
	ui->setupUi(this);
}

SystemManagerWidget::~SystemManagerWidget()
{
	delete ui;
}
