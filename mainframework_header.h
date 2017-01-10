#ifndef MAINFRAMEWORK_HEADER
#define MAINFRAMEWORK_HEADER

#include <QtGlobal>
#include <QDateTime>

struct SoftWorkStatus {
    char messageType;
    QDateTime messageTime;
    char messageContent[128];

};

typedef void* (*findMemoryInfoFunc)(int, uint);//内存申请函数指针
typedef void  (*dllStatusReadFunc)(int);//软件运行状态读函数指针
typedef bool  (*dllStatusWriteFunc)(int);//软件运行状态写函数指针
typedef bool  (*softWorkStatusWriteFunc)(int,SoftWorkStatus);//软件工作状态写函数指针

findMemoryInfoFunc FindMemoryInfoFunc;
dllStatusReadFunc  DllStatusReadFunc;
dllStatusWriteFunc DllStatusWriteFunc;
softWorkStatusWriteFunc SoftWorkStatusWriteFunc;

#endif // MAINFRAMEWORK_HEADER

