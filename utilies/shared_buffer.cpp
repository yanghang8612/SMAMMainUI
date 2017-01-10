#include <string.h>

#include "shared_buffer.h"

SharedBuffer::SharedBuffer(void* headerPointer)
{
    commonInit(headerPointer);
    type = ONLY_READ;
}

SharedBuffer::SharedBuffer(void* headerPointer, quint32 bufferSize, quint32 blockSize, quint32 stationID, quint32 ipAddress)
{
    commonInit(headerPointer);
    type = READ_WRITE;
    header->bufferSize = bufferSize;
    header->blockSize = blockSize;
    header->writePointer = 0;
    header->readAndWriteLock = 0;
    header->stationID = stationID;
    header->ipAddress = ipAddress;
}

quint32 SharedBuffer::readData(void* dataToRead, quint32 lengthToRead)
{
    quint32 length = 0;
    if (readPointer == header->writePointer || lengthToRead == 0) {
        return 0;
    }
    else if (readPointer < header->writePointer) {
        if (header->writePointer - readPointer >= lengthToRead) {
            length = lengthToRead;
        }
        else {
            length = header->writePointer - readPointer;
        }
    }
    else {
        if (header->bufferSize - readPointer > lengthToRead) {
            length = lengthToRead;
        }
        else {
            length = header->bufferSize - readPointer;
            memcpy(dataToRead, dataStartPointer + readPointer, length);
            readPointer = 0;
            return length + readData(dataToRead + length, lengthToRead - length);
        }
    }
    memcpy(dataToRead, dataStartPointer + readPointer, length);
    readPointer += length;
    return length;
}

quint32 SharedBuffer::writeData(const void* dataFromWrite, quint32 lengthFromWrite)
{
    if (lengthFromWrite > header->bufferSize) {
        return -1;
    }
    quint32 bufferTailLength = header->bufferSize - header->writePointer;
    if (bufferTailLength > lengthFromWrite) {
        memcpy(dataStartPointer + header->writePointer, dataFromWrite, lengthFromWrite);
        header->writePointer += lengthFromWrite;
    }
    else {
        memcpy(dataStartPointer + header->writePointer, dataFromWrite, bufferTailLength);
        memcpy(dataStartPointer, dataFromWrite + bufferTailLength, lengthFromWrite - bufferTailLength);
        header->writePointer = lengthFromWrite - bufferTailLength;
    }
    return lengthFromWrite;
}

void SharedBuffer::commonInit(void* headerPointer)
{
    header = (SharedBufferHeader*) headerPointer;
    dataStartPointer = (quint8*) headerPointer + sizeof(SharedBufferHeader);
    readPointer = 0;
}
