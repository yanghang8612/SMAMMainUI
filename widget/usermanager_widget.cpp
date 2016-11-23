#include "usermanager_widget.h"
#include "ui_usermanager_widget.h"

UserManagerWidget::UserManagerWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::UserManagerWidget)
{
	ui->setupUi(this);
}

UserManagerWidget::~UserManagerWidget()
{
	delete ui;
}
