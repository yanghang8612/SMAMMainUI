#ifndef SMAMFRAMEWORK_HEADER
#define SMAMFRAMEWORK_HEADER

#include <QtGlobal>
#include <QString>

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
    char mountPoint[8];
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
    char ipAddress[16];
    int port;
    char username[64];
    char password[64];
    char detail[256];
    char mountPoint[8];
};

struct iGMASStationInBuffer {
    bool isAvailable;
    char stationName[64];
    char mountPoint[8];
    int memID;
    double longitude;
    double latitude;
    double height;
    char detail[256];
};

struct iGMASDataCenterInBuffer {
    bool isAvailable;
    char centerName[64];
    char masterIPAddress[16];
    quint16 masterPort;
    char slaveIPAddress[16];
    quint16 slavePort;
    char username[64];
    char password[64];
    char detail[256];
};

#endif // SMAMFRAMEWORK_HEADER

