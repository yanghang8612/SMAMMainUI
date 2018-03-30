#include <QDebug>

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

void DataTransferStateFrame::setCurrentDataCenter(const QString& centerName, bool isMaster)
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

void DataTransferStateFrame::setRcvdDataLength(long rcvdDataLength)
{
    QString lengthStr = "";
    while (rcvdDataLength != 0) {
        int remainder = rcvdDataLength % 1000;
        rcvdDataLength /= 1000;
        if (rcvdDataLength != 0 && remainder < 10) {
            lengthStr = "00" + QString::number(remainder) + "," + lengthStr;
        }
        else if (rcvdDataLength != 0 && remainder < 100) {
            lengthStr = "0" + QString::number(remainder) + "," + lengthStr;
        }
        else {
            lengthStr = QString::number(remainder) + "," + lengthStr;
        }
    }
    ui->rcvdDataLengthLabel->setText(lengthStr.remove(lengthStr.size() - 1, 1));
}
