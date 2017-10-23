#ifndef DLLSTATEWRITETHREAD_H
#define DLLSTATEWRITETHREAD_H

#include <QThread>

class DllStateWriteThread : public QThread
{
    Q_OBJECT

public:
    explicit DllStateWriteThread();
    void stop();

protected:
    bool isRunning;
    void run();
};

#endif // DLLSTATEWRITETHREAD_H
