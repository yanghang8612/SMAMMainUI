#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <QtGlobal>

class SharedBuffer
{
public:
    enum BufferType {
        LOOP_BUFFER = 0,
        COVER_BUFFER = 1
    };

    enum BufferMode {
        ONLY_READ = 0,
        ONLY_WRITE = 1,
        READ_WRITE = 2
    };

    struct SharedBufferHeader {
        quint32 bufferSize;
        quint32 blockSize;
        quint32 writePointer;
        quint8 readWriteLock;
        quint32 stationID;
        quint32 ipAddress;
        quint8 remainedBufferHeader[56];
    };

public:
    SharedBuffer(BufferType type, BufferMode mode, void* headerPointer);
    SharedBuffer(BufferType type, BufferMode mode, void* headerPointer, quint32 bufferSize, quint32 blockSize);
    SharedBuffer(BufferType type, BufferMode mode, void* headerPointer, quint32 itemSize);
    ~SharedBuffer();

    quint32 readData(void* dataToRead, quint32 lengthOrCountToRead = 0);
    quint32 writeData(const void* dataFromWrite, quint32 lengthOrCountFromWrite);

    quint32 getBufferSize() const;
    quint32 getBlockSize() const;
    quint32 getWritePointer() const;
    quint8 getReadWriteLock() const;

    void setStationID(quint32 stationID);
    quint32 getStationID() const;
    void setIPAddress(quint32 ipAddress);
    quint32 getIPAddress() const;
    void* getDataStartPointer() const;

    quint32 getItemCount() const;
    quint32 getItemSize() const;

private:
    BufferType type;
    BufferMode mode;
    SharedBufferHeader* header;
    quint8* dataStartPointer;

    quint32 readPointer;
    quint32 bufferCapacity;

    quint32* itemCount;
    quint32 itemSize;

    void commonInit(void* headerPointer);
};

#endif // SHAREDBUFFER_H
