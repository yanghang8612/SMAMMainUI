#include "centerinfo_widget.h"
#include "ui_centerinfo_widget.h"

CenterInfoWidget::CenterInfoWidget(QWidget *parent) :
	QTabWidget(parent),
    ui(new Ui::CenterInfoWidget)
{
    ui->setupUi(this);
}

CenterInfoWidget::~CenterInfoWidget()
{
	delete ui;
}

void CenterInfoWidget::setCenter(OtherCenter* center)
{
    this->center = center;
    ui->centerNameEdit->setText(center->getCenterName());
    ui->centerIPEdit->setText(center->getIpAddress());
    ui->centerPortEdit->setText(QString::number(center->getPort()));
    ui->centerDetailEdit->setText(center->getDetail());
}
