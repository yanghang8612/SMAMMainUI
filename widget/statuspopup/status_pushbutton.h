#ifndef STATUSPUSHBUTTON_H
#define STATUSPUSHBUTTON_H

#include <QPushButton>

#include "softwarestatus_frame.h"


class StatusPushButton : public QPushButton
{
    Q_OBJECT

public:
    StatusPushButton(QList<int>& componentStateCheckIntervals, const QIcon& icon, const QString &text, QWidget *parent = 0);

protected:
	virtual void enterEvent(QEvent*);
	virtual void leaveEvent(QEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);

signals:
    void componentStateCheckIntervalsChanged();

private slots:
    void receiveComponentCheckSignal(bool status);
    void modifyComponentStateCheckIntervals(QList<int> newIntervals);

private:
	SoftwareStatusFrame* statusFrame;
    QList<int>& componentStateCheckIntervals;
};

#endif // STATUSPUSHBUTTON_H
