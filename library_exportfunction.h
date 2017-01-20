#ifndef LIBRARY_EXPORTFUNCTION
#define LIBRARY_EXPORTFUNCTION

#include <QThread>

class MySharedMemoryWriteThread : public QThread
{
    Q_OBJECT

public:
    explicit MySharedMemoryWriteThread(void* sharedMemoryPointer, quint32 bufferSize);

protected:
    void run();

private:
    void* sharedMemoryPointer;
    quint32 bufferSize;
};

class MySharedMemoryReadThread : public QThread
{
    Q_OBJECT

public:
    explicit MySharedMemoryReadThread(void* sharedMemoryPointer);

protected:
    void run();

private:
    void* sharedMemoryPointer;
};

#endif // LIBRARY_EXPORTFUNCTION

