#include "softwarestatus_frame.h"
#include "ui_softwarestatus_frame.h"

#include "common.h"
#include "main_component_header.h"

SoftwareStatusFrame::SoftwareStatusFrame(QList<int>& componentStateCheckIntervals, QWidget *parent) :
	QFrame(parent),
    ui(new Ui::SoftwareStatusFrame), componentStateCheckIntervals(componentStateCheckIntervals)
{
	ui->setupUi(this);
    buttons[0] = ui->mainFrameworkStatus;
    buttons[1] = ui->dataCollectAndBroadcastStatus;
    buttons[2] = ui->dataDisposeStatus;
    buttons[3] = ui->dataStorageStatus;
    buttons[4] = ui->userManagerStatus;
    buttons[5] = ui->systemManagerStatus;
    qMemSet(dllStatus, 1, sizeof(dllStatus));
    qMemSet(preDllStatus, 1, sizeof(dllStatus));
    qMemSet(componentStateCheckCountdown, 0, sizeof(componentStateCheckCountdown));
    qMemSet(componentStatus, true, sizeof(componentStatus));
    startTimer(DLLSTATE_CHECK_TIMEINTERVAL);
}

SoftwareStatusFrame::~SoftwareStatusFrame()
{
    delete ui;
}

void SoftwareStatusFrame::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    if (DllStatusReadFunc != 0) {
        DllStatusReadFunc(dllStatus, DLL_COUNT * sizeof(int));
        for (int i = 0; i < COMPONENT_COUNT; i++) {
            if ((++componentStateCheckCountdown[i]) == componentStateCheckIntervals[i]) {
                if (dllStatus[COMPONENT_STATEARRAY_INDEX[i]] == 0) {
                    continue;
                }
                componentStateCheckCountdown[i] = 0;
                componentStatus[i] = true;
                for (int j = 0; j < COMPONENT_DLL_COUNT[i]; j++) {
                    int index = COMPONENT_STATEARRAY_INDEX[i] + j;
                    if (dllStatus[index] == preDllStatus[index]) {
                        componentStatus[i] = false;
                        break;
                    }
                }
                buttons[i]->setIcon(QIcon(componentStatus[i] ? ":/status_green" : ":/status_red"));
                qMemCopy(
                        &preDllStatus[COMPONENT_STATEARRAY_INDEX[i]],
                        &dllStatus[COMPONENT_STATEARRAY_INDEX[i]],
                        COMPONENT_DLL_COUNT[i] * sizeof(int));
            }

        }
        bool status = true;
        for (int i = 0; i < DLL_COUNT; i++) {
            status &= componentStatus[i];
        }
        emit isEveryComponentNormal(status);
    }
}
