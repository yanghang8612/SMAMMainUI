#include "igmasdatacenter_widget.h"
#include "ui_igmasdatacenter_widget.h"

iGMASDataCenterWidget::iGMASDataCenterWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::iGMASDataCenterWidget)
{
    ui->setupUi(this);
}

iGMASDataCenterWidget::~iGMASDataCenterWidget()
{
    delete ui;
}

void iGMASDataCenterWidget::setDataCenter(iGMASDataCenter* dataCenter)
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
