#include "dllstate_write_thread.h"
#include "main_component_header.h"
#include "common.h"

DllStateWriteThread::DllStateWriteThread() :
        QThread()
{
}

void DllStateWriteThread::run()
{
    while (true) {
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

