#ifndef SMAMFRAMEWORK_HEADER
#define SMAMFRAMEWORK_HEADER

#include <QtGlobal>

#define MAX_RECEIVER_COUNT 2

struct ReceiverInBuffer {
    int memID;
    char receiverName[64];
    char password[64];
    char ipAddress[16];
    quint16 port;
    float longitude;
    float latitude;
    float height;
    char detail[256];
    char mount[8];
};

struct StandardStationInBuffer {
    char stationName[64];
    char detail[256];
    quint8 deploymentType;
    quint8 receiverCount;
    ReceiverInBuffer receivers[MAX_RECEIVER_COUNT];
};

struct OtherCenterInBuffer {
    char centerName[64];
    char userName[64];
    char password[64];
    char ipAddress[16];
    int port;
    char detail[256];
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
    char userName[64];
    char password[64];
};

struct IGSStationInBuffer {
    char stationName[64];
    char ipAddress[16];
    quint16 port;
};

#endif // SMAMFRAMEWORK_HEADER

