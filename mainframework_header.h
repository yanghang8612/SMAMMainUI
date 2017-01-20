#ifndef MAINFRAMEWORK_HEADER
#define MAINFRAMEWORK_HEADER

#include <QtGlobal>
#include <ctime>

struct SoftWorkStatus {
    char messageContent[128];
    time_t messageTime;
    char messageType;
};

typedef void* (*FINDMEMORYINFOFUNC)(int, uint);//内存申请函数指针
typedef void  (*DLLSTATUSREADFUNC)(int*, int);//软件运行状态读函数指针
typedef bool  (*DLLSTATUSWRITEFUNC)(int);//软件运行状态写函数指针
typedef bool  (*SOFTWORKSTATUSWRITEFUNC)(int,SoftWorkStatus);//软件工作状态写函数指针

extern FINDMEMORYINFOFUNC findMemoryInfoFunc;
extern DLLSTATUSREADFUNC  dllStatusReadFunc;
extern DLLSTATUSWRITEFUNC dllStatusWriteFunc;
extern SOFTWORKSTATUSWRITEFUNC softWorkStatusWriteFunc;

#endif // MAINFRAMEWORK_HEADER

