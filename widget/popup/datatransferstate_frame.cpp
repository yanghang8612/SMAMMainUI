#include "datatransferstate_frame.h"
#include "ui_datatransferstate_frame.h"

DataTransferStateFrame::DataTransferStateFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataTransferStateFrame)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    ui->masterRadio->setChecked(true);
}

DataTransferStateFrame::~DataTransferStateFrame()
{
    delete ui;
}

void DataTransferStateFrame::setState(const QString& centerName, bool isMaster)
{
    ui->dataCenterNameLabel->setText(centerName);
    if (isMaster) {
        ui->masterRadio->setChecked(true);
        ui->slaveRadio->setChecked(false);
    }
    else {
        ui->masterRadio->setChecked(false);
        ui->slaveRadio->setChecked(true);
    }
}
