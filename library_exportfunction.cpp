#include <QWidget>
#include <QDebug>

#include "main_component_header.h"
#include "other_component_header.h"
#include "systemmanager_widget.h"
#include "backend/dllstate_write_thread.h"
#include "utilities/config_helper.h"

DeploymentType::Value deploymentType;

void* receiverSharedBufferPointer = 0;
void* monitorStationSharedBufferPointer = 0;
void* dataCenterSharedBufferPointer = 0;
void* otherCenterSharedBufferPointer = 0;

void* componentStateSharedBufferPointer[COMPONENT_COUNT];
void* userRegisterInfoSharedBufferPointer = 0;
void* userRealtimeInfoSharedBufferPointer = 0;

static DllStateWriteThread* dllStateWriteThread = 0;
static SystemManagerWidget* widget = 0;

extern "C" bool DllMain(int args, char* argv[])
{
    qDebug() << "SMAMMainUI:" << "DllMain function called";

    if (args > 0 && qstrcmp(argv[0], "XJ") == 0) {
        deploymentType = DeploymentType::XJ_CENTER;
        receiverSharedBufferPointer = FindMemoryInfoFunc(RECEIVER_SHAREDBUFFER_ID,
                                                         RECEIVER_MAXITEMCOUNT * sizeof(ReceiverInBuffer));
    }
    else if (args > 0 && qstrcmp(argv[0], "BJ") == 0) {
        deploymentType = DeploymentType::BJ_CENTER;
        monitorStationSharedBufferPointer = FindMemoryInfoFunc(MONITORSTATION_SHAREDBUFFER_ID,
                                                      MONITORSTATION_MAXITEMCOUNT * sizeof(MonitorStationInBuffer));

        dataCenterSharedBufferPointer = FindMemoryInfoFunc(DATACENTER_SHAREDBUFFER_ID,
                                                      DATACENTER_MAXITEMCOUNT * sizeof(DataCenterInBuffer));

        otherCenterSharedBufferPointer = FindMemoryInfoFunc(OTHERCENTER_SHAREDBUFFER_ID,
                                                            OTHERCENTER_MAXITEMCOUNT * sizeof(OtherCenterInBuffer));
    }
    else {
        qDebug() << "SMAMMainUI:" << "No appropriate deployment type according to parameter 'argv'";
        return false;
    }
    ConfigHelper::init();
    return true;
}

extern "C" bool DllInit(int, char*)
{
    qDebug() << "SMAMMainUI:" << "DllInit function called";

    dllStateWriteThread = new DllStateWriteThread();
    dllStateWriteThread->start();

    for (int i = 0; i < COMPONENT_COUNT; i++) {
        componentStateSharedBufferPointer[i] = FindMemoryInfoFunc(i + 2, 0);
    }

    userRegisterInfoSharedBufferPointer = FindMemoryInfoFunc(
                                              USER_REGISTER_INFO_SHAREDBUFFER_ID,
                                              USER_REGISTER_INFO_MAXITEMCOUNT * sizeof(UserBasicInfo) + sizeof(int));

    userRealtimeInfoSharedBufferPointer = FindMemoryInfoFunc(
                                              USER_REALTIME_INFO_SHAREDBUFFER_ID,
                                              USER_REALTIME_INFO_MAXITEMCOUNT * sizeof(UserLoginInfo) + sizeof(int));
    return true;
}

extern "C" bool DllStart()
{
    qDebug() << "SMAMMainUI:" << "DllStart function called";
    widget = new SystemManagerWidget();
    return true;
}

extern "C" bool DllStop()
{
    qDebug() << "SMAMMainUI:" << "DllStop function called";
    dllStateWriteThread->stop();
    return true;
}

extern "C" bool DllContraryInit()
{
    qDebug() << "SMAMMainUI:" << "DllContraryInit function called";
    delete widget;
    delete dllStateWriteThread;
    return true;
}

extern "C" QString getUIName()
{
    return QObject::tr("系统监控管理");
}

extern "C" QWidget* getUIWidget(QWidget* parent = 0)
{
    widget->setParent(parent);
    return widget;
}
