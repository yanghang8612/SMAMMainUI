#include <QWidget>
#include <QDebug>

#include "library_exportfunction.h"
#include "mainframework_header.h"
#include "widget/mid/systemmanager_widget.h"
#include "utilies/shared_buffer.h"

MySharedMemoryWriteThread::MySharedMemoryWriteThread(void* sharedMemoryPointer) :
        QThread(),
        sharedMemoryPointer(sharedMemoryPointer)
{

}

void MySharedMemoryWriteThread::run()
{
    SharedBuffer buffer(sharedMemoryPointer, 100);
    while (true) {
        quint8* data = new quint8[15];
        for (int i = 0; i < 15; i++) {
            data[i] = qrand() % 255;
        }
        buffer.writeData(data, 15);
        sleep(2);
    }
}

extern "C" bool DllMain(int argc, char* argv[])
{
    qDebug() << "SMAM DllMain function called.";
    void* myFirstSharedMemoryPointer = (FindMemoryInfoFunc)(100, 200);
    //void* myFirstSharedMemoryPointer = new quint8[180];
    qDebug() << "Alloc shared memory address :" << myFirstSharedMemoryPointer;
    MySharedMemoryWriteThread* writeThread = new MySharedMemoryWriteThread(myFirstSharedMemoryPointer);
    writeThread->start();
    return true;
}

extern "C" bool DllInit(int argc, char* argv[])
{
    qDebug() << "SMAM DllInit function called.";
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
    return new SystemManagerWidget((DeploymentType::Value) 0, parent);
}
