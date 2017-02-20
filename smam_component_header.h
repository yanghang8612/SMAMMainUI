#ifndef SMAMFRAMEWORK_HEADER
#define SMAMFRAMEWORK_HEADER

#include <QtGlobal>

#define MAX_RECEIVER_COUNT 5

struct ReceiverInBuffer {
    char receiverName[64];
    char ipAddress[16];
    quint16 port;
    float longitude;
    float latitude;
    float height;
};

struct StandardStationInBuffer {
    char stationName[64];
    char detail[256];
    char ipAddress[16];
    quint16 port;
    quint8 deploymentType;
    quint8 casterMode;
    quint8 serviceThreadCount;
    quint8 receiverCount;
    ReceiverInBuffer receivers[MAX_RECEIVER_COUNT];
};

struct OtherCenterInBuffer {
    char centerName[64];
    char ipAddress[16];
    quint16 port;
};

struct IGMASStationInBuffer {
    bool isAvailable;
    char ipAddress[16];
    int port;
    char mount[4];
    int memID;
    double longitude;
    double latitude;
    double height;
};

struct IGSStationInBuffer {
    char stationName[64];
    char ipAddress[16];
    quint16 port;
};

#endif // SMAMFRAMEWORK_HEADER

