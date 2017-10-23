#include "dllstate_write_thread.h"

#include "common.h"
#include "main_component_header.h"

DllStateWriteThread::DllStateWriteThread() :
    QThread(), isRunning(true)
{}

void DllStateWriteThread::stop()
{
    isRunning = false;
}

void DllStateWriteThread::run()
{
    while (isRunning) {
        DllStatusWriteFunc(01);
        DllStatusWriteFunc(02);
        DllStatusWriteFunc(03);
        DllStatusWriteFunc(51);
        DllStatusWriteFunc(52);
        DllStatusWriteFunc(53);
        DllStatusWriteFunc(54);
        msleep(DLLSTATE_WRITE_TIMEINTERVAL);
    }
}

