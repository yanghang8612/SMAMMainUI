#ifndef OTHER_COMPONENT_HEADER_H
#define OTHER_COMPONENT_HEADER_H

#include <time.h>

struct UserBasicInfo {
    // long userID;
    char userName[64];
    char pwd[16];
    char terminalNO[16];
    char TEL[16];
    char userLevel[2];
    char broadcastFre[2];
};//1501

struct gtime_t {
    time_t time;
    int second;
};

struct UserLoginInfo {
    bool status;
    char name[64];
    char ip[16];
    //  long id;
    gtime_t timeStart;
    int timeInternal;
    int inforSendNumber;
    gtime_t timeDisconnect;
};//101

struct ReceiverState {
    bool isConnected;
    char mount[8];
};//102

#endif // OTHER_COMPONENT_HEADER_H

