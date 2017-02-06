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

struct iGSStationInBuffer {
    char stationName[64];
    char ipAddress[16];
    quint16 port;
};

struct iGMASStationInBuffer {
    char stationName[64];
    char ipAddress[16];
    quint16 port;
};

#endif // SMAMFRAMEWORK_HEADER

