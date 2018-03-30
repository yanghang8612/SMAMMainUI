#include "datacenter_widget.h"
#include "ui_datacenter_widget.h"

DataCenterWidget::DataCenterWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::DataCenterWidget)
{
    ui->setupUi(this);
    this->hide();
}

DataCenterWidget::~DataCenterWidget()
{
    delete ui;
}

void DataCenterWidget::setDataCenter(DataCenter* dataCenter)
{
    ui->centerNameEdit->setText(dataCenter->getCenterName());
    ui->usernameEdit->setText(dataCenter->getUsername());
    ui->passwordEdit->setText(dataCenter->getPassword());
    ui->masterIPEdit->setText(dataCenter->getMasterIPAddress());
    ui->masterPortEdit->setText(QString::number(dataCenter->getMasterPort()));
    ui->slaveIPEdit->setText(dataCenter->getSlaveIPAddress());
    ui->slavePortEdit->setText(QString::number(dataCenter->getSlavePort()));
    ui->centerDetailEdit->setText(dataCenter->getCenterDetail());
}
