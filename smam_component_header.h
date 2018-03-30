#ifndef SMAMFRAMEWORK_HEADER
#define SMAMFRAMEWORK_HEADER

#define MAX_RECEIVER_COUNT 2

struct DMS {
    int degree;
    int minute;
    int second;
    int fractionalPart;
};

struct ReceiverInBuffer {
    int memID;
    char receiverName[64];
    char password[64];
    char ipAddress[16];
    unsigned short port;
    char mountPoint[8];
    DMS longitude;
    DMS latitude;
    double height;
    char receiverDetail[256];
};

struct StandardStationInBuffer {
    char stationName[64];
    char detail[256];
    char deploymentType;
    int receiverCount;
    ReceiverInBuffer receivers[MAX_RECEIVER_COUNT];
};

struct OtherCenterInBuffer {
    int centerID;
    char centerName[64];
    char ipAddress[16];
    char username[64];
    char password[64];
    char centerDetail[256];
};

struct MonitorStationInBuffer {
    int memID;
    bool isAvailable;
    char stationName[64];
    char mountPoint[8];
    DMS longitude;
    DMS latitude;
    double height;
    char stationDetail[256];
    char dataCenters[64];
};

struct DataCenterInBuffer {
    int centerID;
    char centerName[64];
    char masterIPAddress[16];
    unsigned short masterPort;
    char slaveIPAddress[16];
    unsigned short slavePort;
    char username[64];
    char password[64];
    char centerDetail[256];
};

#endif // SMAMFRAMEWORK_HEADER
