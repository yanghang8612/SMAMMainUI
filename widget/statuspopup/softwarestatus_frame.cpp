#include <QDebug>

#include "softwarestatus_frame.h"
#include "ui_softwarestatus_frame.h"
#include "mainframework_header.h"
#include "common.h"

SoftwareStatusFrame::SoftwareStatusFrame(QWidget *parent) :
	QFrame(parent),
    ui(new Ui::SoftwareStatusFrame), dllStatus(new int[DLL_COUNT]), preDllStatus(new int[DLL_COUNT])
{
	ui->setupUi(this);
    buttons[0] = ui->mainFrameworkStatus;
    buttons[1] = ui->dataCollectAndBroadcastStatus;
    buttons[2] = ui->dataDisposeStatus;
    buttons[3] = ui->dataStorageStatus;
    buttons[4] = ui->userManagerStatus;
    buttons[5] = ui->systemManagerStatus;
    startTimer(DLLSTATUS_CHECK_TIMEINTERVAL);
    qMemSet(preDllStatus, 0, DLL_COUNT * sizeof(int));
}

SoftwareStatusFrame::~SoftwareStatusFrame()
{
    delete ui;
}

void SoftwareStatusFrame::timerEvent(QTimerEvent* event)
{
    for (int i = 0; i < DLL_COUNT; i++) {
        qDebug() << dllStatus[i] << preDllStatus[i];
    }
    if (DllStatusReadFunc != 0) {
        DllStatusReadFunc(dllStatus, DLL_COUNT * sizeof(int));
        for (int i = 0; i < 6; ++i) {
            QString status = ":/status_green";
            for (int j = 0; j < COMPONENT_DLL_COUNT[i]; ++j) {
                int index = COMPONENT_STATUSARRAY_INDEX[i] + j;
                if (dllStatus[index] == preDllStatus[index]) {
                    status = ":/status_red";
                    break;
                }
            }
            buttons[i]->setIcon(QIcon(status));
        }
        qMemCopy(preDllStatus, dllStatus, DLL_COUNT * sizeof(int));
    }
}
