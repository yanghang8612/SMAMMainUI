#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <QtGlobal>

struct SharedBufferHeader {
    quint32 bufferSize;
    quint32 blockSize;
    quint32 writePointer;
    quint8 readWriteLock;
    quint32 stationID;
    quint32 ipAddress;
    quint8 remainedBufferHeader[56];
};

enum BufferType{
    ONLY_READ = 0,
    READ_WRITE = 1
};

class SharedBuffer
{
public:
    SharedBuffer(void* headerPointer);
    SharedBuffer(void* headerPointer, quint32 bufferSize, quint32 blockSize = 1, quint32 stationID = 0, quint32 ipAddress = 0);
    ~SharedBuffer();

    quint32 readData(void* dataToRead, quint32 lengthToRead);
    quint32 writeData(const void* dataFromWrite, quint32 lengthFromWrite);

    quint32 getBufferSize() const;
    quint32 getBlockSize() const;
    quint32 getWritePointer() const;
    quint8 getReadWriteLock() const;
    void setStationID(quint32 stationID);
    quint32 getStationID() const;
    void setIPAddress(quint32 ipAddress);
    quint32 getIPAddress() const;
    void* getDataStartPointer() const;

private:
    SharedBufferHeader* header;
    quint8* dataStartPointer;
    quint32 readPointer;
    BufferType type;

    void commonInit(void* headerPointer);
};

#endif // SHAREDBUFFER_H
