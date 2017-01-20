#ifndef SOFTWARESTATUS_FRAME_H
#define SOFTWARESTATUS_FRAME_H

#include <QFrame>
#include <QPushButton>

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
    int* dllStatus;
    int* preDllStatus;
    QPushButton* buttons[6];
};

#endif // SOFTWARESTATUS_FRAME_H
