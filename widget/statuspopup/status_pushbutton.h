#ifndef STATUSPUSHBUTTON_H
#define STATUSPUSHBUTTON_H

#include <QPushButton>

#include "softwarestatus_frame.h"


class StatusPushButton : public QPushButton
{
    Q_OBJECT

public:
    StatusPushButton(const QIcon& icon, const QString &text, QWidget *parent = 0);

protected:
	virtual void enterEvent(QEvent*);
	virtual void leaveEvent(QEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);

private slots:
    void receiveComponentCheckSignal(bool status);

private:
    SoftwareStatusFrame* statusFrame;
};

#endif // STATUSPUSHBUTTON_H
