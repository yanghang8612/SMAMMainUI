#ifndef SMAMFRAMEWORK_HEADER
#define SMAMFRAMEWORK_HEADER

#include <QList>
#include <QString>

struct ReceiverInBuffer {
    QString receiverName;
    QString ipAddress;
    quint16 port;
    float longitude;
    float latitude;
};

struct StandardStationInBuffer {
    QString stationName;
    QString detail;
    QString ipAddress;
    quint16 port;
    quint8 deploymentType;
    quint8 casterMode;
    quint8 serviceThreadCount;
    QList<ReceiverInBuffer> receivers;
};

#endif // SMAMFRAMEWORK_HEADER

