#include "datatransferstate_frame.h"
#include "ui_datatransferstate_frame.h"

DataTransferStateFrame::DataTransferStateFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataTransferStateFrame)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
}

DataTransferStateFrame::~DataTransferStateFrame()
{
    delete ui;
}
