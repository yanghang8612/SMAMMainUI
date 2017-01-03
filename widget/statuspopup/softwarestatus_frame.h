#ifndef SOFTWARESTATUS_FRAME_H
#define SOFTWARESTATUS_FRAME_H

#include <QFrame>

namespace Ui {
	class SoftwareStatusFrame;
}

class SoftwareStatusFrame : public QFrame
{
	Q_OBJECT

public:
	explicit SoftwareStatusFrame(QWidget *parent = 0);
	~SoftwareStatusFrame();

signals:
    void isEveryComponentNormal(bool);

private:
	Ui::SoftwareStatusFrame *ui;
};

#endif // SOFTWARESTATUS_FRAME_H
