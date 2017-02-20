#include <QWidget>
#include <QDebug>

#include "library_exportfunction.h"
#include "main_component_header.h"
#include "widget/mid/systemmanager_widget.h"
#include "utilies/shared_buffer.h"

static SystemManagerWidget* widget = 0;

MySharedMemoryWriteThread::MySharedMemoryWriteThread(void* sharedMemoryPointer, quint32 bufferSize) :
        QThread(),
        sharedMemoryPointer(sharedMemoryPointer), bufferSize(bufferSize)
{
}

void MySharedMemoryWriteThread::run()
{
    //SharedBuffer buffer(SharedBuffer::LOOP_BUFFER, SharedBuffer::ONLY_WRITE, sharedMemoryPointer, bufferSize, 1);
    while (true) {
        SoftWorkStatus* status = new SoftWorkStatus;
        qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
        status->messageType = qrand() % 3 + 1;
        status->messageTime = time(0);
        const char* message;
        switch (status->messageType) {
            case 1:
                message = QString(tr("这是一条正常消息")).toStdString().c_str();
                break;
            case 2:
                message = QString(tr("这是一条告警消息")).toStdString().c_str();
                break;
            case 3:
                message = QString(tr("这是一条错误消息")).toStdString().c_str();
                break;
            default:
                message = QString(tr("这是一条空消息")).toStdString().c_str();
                break;
        }
        qMemSet(status->messageContent, 0, sizeof(status->messageContent));
        qMemCopy(status->messageContent, message, qstrlen(message));
        //qDebug() << "In write thread, message length is" << qstrlen(status->messageContent) << "message is" << QString(status->messageContent);
        //buffer.writeData(status, sizeof(SoftWorkStatus));
        DllStatusWriteFunc(51);
        DllStatusWriteFunc(52);
        DllStatusWriteFunc(53);
        DllStatusWriteFunc(54);
        SoftWorkStatusWriteFunc(6, *status);
        sleep(qrand() % 3 + 1);
    }
}

MySharedMemoryReadThread::MySharedMemoryReadThread(void* sharedMemoryPointer) :
    QThread(),
    sharedMemoryPointer(sharedMemoryPointer)
{

}

void MySharedMemoryReadThread::run()
{
    SharedBuffer buffer(SharedBuffer::LOOP_BUFFER, SharedBuffer::ONLY_READ, sharedMemoryPointer);
    while (true) {
        SoftWorkStatus* status = new SoftWorkStatus;
        int code = buffer.readData(status, sizeof(SoftWorkStatus));
        if (code > 0) {
            qDebug() << "Message time:" << QDateTime::fromTime_t(status->messageTime);
            qDebug() << "In read thread, message is" << status->messageContent;
        }
        msleep(100);
    }
}

extern "C" bool DllMain(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    qDebug() << "SMAM DllMain function called.";
    void* myFirstSharedMemoryPointer = FindMemoryInfoFunc(7, 1520);
    MySharedMemoryWriteThread* writeThread = new MySharedMemoryWriteThread(myFirstSharedMemoryPointer, 1520);
    writeThread->start();
    widget = new SystemManagerWidget((DeploymentType::Value) 1, 0);
//    MySharedMemoryReadThread* readThread = new MySharedMemoryReadThread(myFirstSharedMemoryPointer);
//    readThread->start();
    return true;
}

extern "C" bool DllInit(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
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
    widget->setParent(parent);
    return widget;
}
