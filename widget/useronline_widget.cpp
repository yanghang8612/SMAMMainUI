#include "useronline_widget.h"
#include "ui_useronline_widget.h"

UserOnlineWidget::UserOnlineWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::UserOnlineWidget)
{
	ui->setupUi(this);
}

UserOnlineWidget::~UserOnlineWidget()
{
	delete ui;
}
