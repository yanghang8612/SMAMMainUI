#include <QWidget>
#include <QDebug>

#include "main_component_header.h"
#include "backend/dllstate_write_thread.h"
#include "widget/mid/systemmanager_widget.h"

void* receiverSharedBufferPointer = 0;
void* otherCenterSharedBufferPointer = 0;
void* iGMASSharedBufferPointer = 0;

void* componentStateSharedBufferPointer[COMPONENT_COUNT];
void* receiverStateSharedBufferPointer = 0;

static SystemManagerWidget* widget = 0;

extern "C" bool DllMain(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    qDebug() << "SMAM DllMain function called.";

    DllStateWriteThread* dllStateWriteThread = new DllStateWriteThread();
    dllStateWriteThread->start();

    receiverSharedBufferPointer = FindMemoryInfoFunc(RECEIVER_SHAREDBUFFER_ID,
                                                     RECEIVER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(ReceiverInBuffer));

    otherCenterSharedBufferPointer = FindMemoryInfoFunc(OTHERCENTER_SHAREDBUFFER_ID,
                                                        OTHERCENTER_SHAREDBUFFER_MAXITEMCOUNT * sizeof(OtherCenterInBuffer));

    iGMASSharedBufferPointer = FindMemoryInfoFunc(IGMAS_SHAREDBUFFER_ID,
                                                  IGMAS_SHAREDBUFFER_MAXITEMCOUNT * sizeof(IGMASStationInBuffer));

    widget = new SystemManagerWidget(DeploymentType::XJ_CENTER);

    return true;
}

extern "C" bool DllInit(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    qDebug() << "SMAM DllInit function called.";

    for (int i = 0; i < COMPONENT_COUNT; i++) {
        componentStateSharedBufferPointer[i] = FindMemoryInfoFunc(i + 2, 0);
    }

    receiverStateSharedBufferPointer = FindMemoryInfoFunc(RECEIVER_STATE_SHAREDBUFFER_ID, 0);

    return true;
}

extern "C" bool DllStart()
{
    qDebug() << "SMAM DllStart function called.";
    return true;
}

extern "C" bool DllStop()
{
    qDebug() << "SMAM DllStop function called.";
    return true;
}

extern "C" bool DllContraryInit()
{
    qDebug() << "SMAM DllContraryInit function called.";
    return true;
}

extern "C" QWidget* getUIWidget(QWidget* parent = 0)
{
    widget->setParent(parent);
    return widget;
}
