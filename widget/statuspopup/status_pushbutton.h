#ifndef STATUSPUSHBUTTON_H
#define STATUSPUSHBUTTON_H

#include <QPushButton>

#include "softwarestatus_frame.h"


class StatusPushButton : public QPushButton
{
    Q_OBJECT

public:
	StatusPushButton(const QIcon& icon, const QString &text, QWidget *parent = 0);

private slots:
    void receiveComponentCheckSignal(bool status);

protected:
	virtual void enterEvent(QEvent*);
	virtual void leaveEvent(QEvent* event);

private:
	SoftwareStatusFrame* statusFrame;
};

#endif // STATUSPUSHBUTTON_H
