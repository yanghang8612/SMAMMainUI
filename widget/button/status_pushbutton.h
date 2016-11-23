#ifndef STATUSPUSHBUTTON_H
#define STATUSPUSHBUTTON_H

#include <QPushButton>

#include "widget/softwarestatus_frame.h"


class StatusPushButton : public QPushButton
{
public:
	StatusPushButton(const QIcon& icon, const QString &text, QWidget *parent = 0);

protected:
	virtual void enterEvent(QEvent* event);
	virtual void leaveEvent(QEvent* event);

private:
	SoftwareStatusFrame* statusFrame = 0;
};

#endif // STATUSPUSHBUTTON_H
