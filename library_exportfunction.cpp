#include <QWidget>
#include <QDebug>

#include "main_component_header.h"
#include "backend/dllstate_write_thread.h"
#include "widget/mid/systemmanager_widget.h"

extern DeploymentType::Value deploymentType;

void* receiverSharedBufferPointer = 0;
void* otherCenterSharedBufferPointer = 0;
void* iGMASSharedBufferPointer = 0;

void* componentStateSharedBufferPointer[COMPONENT_COUNT];
void* receiverStateSharedBufferPointer = 0;
void* iGMASStateSharedBufferPointer = 0;
void* otherCenterStateSharedBufferPointer = 0;

static SystemManagerWidget* widget = 0;

extern "C" bool DllMain(int args, char* argv[])
{
    qDebug() << "SMAMMainUI:" << "DllMain function called";

    DllStateWriteThread* dllStateWriteThread = new DllStateWriteThread();
    dllStateWriteThread->start();

    otherCenterSharedBufferPointer = FindMemoryInfoFunc(OTHERCENTER_SHAREDBUFFER_ID,
                                                        OTHERCENTER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(OtherCenterInBuffer));

    if (args > 0 && qstrcmp(argv[0], "XJ")) {
        receiverSharedBufferPointer = FindMemoryInfoFunc(RECEIVER_SHAREDBUFFER_ID,
                                                         RECEIVER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(ReceiverInBuffer));

        widget = new SystemManagerWidget(DeploymentType::XJ_CENTER);
    }
    else if (args > 0 && qstrcmp(argv[0], "BJ")) {
        iGMASSharedBufferPointer = FindMemoryInfoFunc(IGMAS_SHAREDBUFFER_ID,
                                                      IGMAS_SHAREDBUFFER_MAXITEMCOUNT * sizeof(IGMASStationInBuffer));

        widget = new SystemManagerWidget(DeploymentType::BJ_CENTER);
    }
    else {
        qDebug() << "SMAMMainUI:" << "No appropriate deployment type according to parameter 'argv'";
        return false;
    }

    return true;
}

extern "C" bool DllInit(int, char*)
{
    qDebug() << "SMAMMainUI:" << "DllInit function called";

    for (int i = 0; i < COMPONENT_COUNT; i++) {
        componentStateSharedBufferPointer[i] = FindMemoryInfoFunc(i + 2, 0);
    }

    switch (deploymentType) {
        case DeploymentType::XJ_CENTER:
            receiverStateSharedBufferPointer = FindMemoryInfoFunc(RECEIVER_STATE_SHAREDBUFFER_ID, RECEIVER_STATE_SHAREDBUFFER_MAXITEMCOUNT * 17);
            break;
        case DeploymentType::BJ_CENTER:
            iGMASStateSharedBufferPointer = FindMemoryInfoFunc(IGMAS_STATE_SHAREDBUFFER_ID, IGMAS_STATE_SHAREDBUFFER_MAXITEMCOUNT * 17);
            break;
    }
    otherCenterStateSharedBufferPointer = FindMemoryInfoFunc(OTHERCENTER_STATE_SHAREDBUFFER_ID, OTHERCENTER_STATE_SHAREDBUFFER_MAXITEMCOUNT * 17);

    return true;
}

extern "C" bool DllStart()
{
    qDebug() << "SMAMMainUI:" << "DllStart function called";
    return true;
}

extern "C" bool DllStop()
{
    qDebug() << "SMAMMainUI:" << "DllStop function called";
    return true;
}

extern "C" bool DllContraryInit()
{
    qDebug() << "SMAMMainUI:" << "DllContraryInit function called";
    return true;
}

extern "C" QWidget* getUIWidget(QWidget* parent = 0)
{
    widget->setParent(parent);
    return widget;
}
