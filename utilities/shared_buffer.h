#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <QtGlobal>

class SharedBuffer
{
public:
    struct SharedBufferHeader {
        quint32 bufferSize;
        quint32 blockSize;
        quint32 writePointer;
        quint32 readWriteLock;
        quint32 stationID;
        quint32 ipAddress;
        quint32 isDirty;
        quint8 remainedBufferHeader[52];
    };

public:
    SharedBuffer(void* headerPointer);
    SharedBuffer(void* headerPointer, quint32 bufferSize, quint32 blockSize);

    quint32 readData(void* dataToRead, quint32 lengthToRead = 0);
    quint32 writeData(const void* dataFromWrite, quint32 lengthFromWrite);

    quint32 getBufferSize() const;
    quint32 getBlockSize() const;
    quint32 getWritePointer() const;
    quint32 getReadWriteLock() const;
    bool isDirty() const;
    void setDirty();

    void setStationID(quint32 stationID);
    quint32 getStationID() const;
    void setIPAddress(quint32 ipAddress);
    quint32 getIPAddress() const;
    void* getDataStartPointer() const;

    bool getDataWriteState();

private:
    SharedBufferHeader* header;
    quint8* dataStartPointer;
    quint32 readPointer;
    quint32 bufferCapacity;
    quint32 preWritePointer;

    void commonInit(void* headerPointer);
};

#endif // SHAREDBUFFER_H
