#ifndef SOFTWARESTATUS_FRAME_H
#define SOFTWARESTATUS_FRAME_H

#include <QFrame>
#include <QPushButton>

#include "common.h"
#include "utilies/shared_buffer.h"

namespace Ui {
	class SoftwareStatusFrame;
}

class SoftwareStatusFrame : public QFrame
{
	Q_OBJECT

public:
	explicit SoftwareStatusFrame(QWidget *parent = 0);
	~SoftwareStatusFrame();

protected:
    void timerEvent(QTimerEvent* event);

signals:
    void isEveryComponentNormal(bool);

private:
	Ui::SoftwareStatusFrame *ui;
    int dllStatus[DLL_COUNT];
    int preDllStatus[DLL_COUNT];
    QPushButton* buttons[DLL_COUNT];
    bool componentStatus[DLL_COUNT];
};

#endif // SOFTWARESTATUS_FRAME_H
