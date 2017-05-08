#include <QWidget>
#include <QDebug>

#include "main_component_header.h"
#include "other_component_header.h"
#include "backend/dllstate_write_thread.h"
#include "widget/mid/systemmanager_widget.h"

extern DeploymentType::Value deploymentType;

void* receiverSharedBufferPointer = 0;
void* otherCenterSharedBufferPointer = 0;
void* iGMASSharedBufferPointer = 0;
void* DMZSharedBufferPointer = 0;

void* componentStateSharedBufferPointer[COMPONENT_COUNT];
void* receiverStateSharedBufferPointer = 0;
void* iGMASStateSharedBufferPointer = 0;
void* otherCenterStateSharedBufferPointer = 0;

void* userRegisterInfoSharedBufferPointer = 0;
void* userRealtimeInfoSharedBufferPointer = 0;

static SystemManagerWidget* widget = 0;

extern "C" bool DllMain(int args, char* argv[])
{
    qDebug() << "SMAMMainUI:" << "DllMain function called";

    DllStateWriteThread* dllStateWriteThread = new DllStateWriteThread();
    dllStateWriteThread->start();

    otherCenterSharedBufferPointer = FindMemoryInfoFunc(OTHERCENTER_SHAREDBUFFER_ID,
                                                        OTHERCENTER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(OtherCenterInBuffer));

    if (args > 0 && qstrcmp(argv[0], "XJ") == 0) {
        receiverSharedBufferPointer = FindMemoryInfoFunc(RECEIVER_SHAREDBUFFER_ID,
                                                         RECEIVER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(ReceiverInBuffer));

        DMZSharedBufferPointer = FindMemoryInfoFunc(DMZ_SHAREDBUFFER_ID, 1);

        widget = new SystemManagerWidget(DeploymentType::XJ_CENTER);
    }
    else if (args > 0 && qstrcmp(argv[0], "BJ") == 0) {
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
            receiverStateSharedBufferPointer = FindMemoryInfoFunc(
                                                   RECEIVER_STATE_SHAREDBUFFER_ID,
                                                   RECEIVER_STATE_SHAREDBUFFER_MAXITEMCOUNT * sizeof(ReceiverState) + sizeof(int));

            userRegisterInfoSharedBufferPointer = FindMemoryInfoFunc(
                                                      USER_REGISTER_INFO_SHAREDBUFFER_ID,
                                                      USER_REGISTER_INFO_SHAREDBUFFER_MAXITEMCOUNT * sizeof(UserBasicInfo) + sizeof(int));

            userRealtimeInfoSharedBufferPointer = FindMemoryInfoFunc(
                                                      USER_REALTIME_INFO_SHAREDBUFFER_ID,
                                                      USER_REALTIME_INFO_SHAREDBUFFER_MAXITEMCOUNT * sizeof(UserLoginInfo) + sizeof(int));
            break;
        case DeploymentType::BJ_CENTER:
            iGMASStateSharedBufferPointer = FindMemoryInfoFunc(
                                                IGMAS_STATE_SHAREDBUFFER_ID,
                                                IGMAS_STATE_SHAREDBUFFER_MAXITEMCOUNT * sizeof(IGMASState) + sizeof(int));
            break;
    }
    otherCenterStateSharedBufferPointer = FindMemoryInfoFunc(
                                              OTHERCENTER_STATE_SHAREDBUFFER_ID,
                                              OTHERCENTER_STATE_SHAREDBUFFER_MAXITEMCOUNT * sizeof(OtherCenterState) + sizeof(int));

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
