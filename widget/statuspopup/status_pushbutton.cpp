#include <QDebug>

#include "status_pushbutton.h"
#include "widget/dialog/modify_component_state_check_intervals_dialog.h"

StatusPushButton::StatusPushButton(QList<int>& componentStateCheckIntervals, const QIcon& icon, const QString& text, QWidget* parent) :
    QPushButton(icon, text, parent),
    componentStateCheckIntervals(componentStateCheckIntervals)
{
	this->setStyleSheet("QPushButton{border-style:none}");
    statusFrame = new SoftwareStatusFrame(componentStateCheckIntervals, parent);
    statusFrame->setStyleSheet(QString("QFrame{border: 1px solid gray;background-color: white;}QPushButton {border-style: none;font: 12px;}"));
    statusFrame->hide();
    connect(statusFrame, SIGNAL(isEveryComponentNormal(bool)), this, SLOT(receiveComponentCheckSignal(bool)));
}

void StatusPushButton::enterEvent(QEvent*)
{
    statusFrame->setGeometry(this->pos().x() + 150, this->pos().y() + 30, 160, 200);
    statusFrame->show();
}

void StatusPushButton::leaveEvent(QEvent*)
{
    statusFrame->hide();
}

void StatusPushButton::mousePressEvent(QMouseEvent*)
{
    ModifyComponentStateCheckIntervalsDialog* dialog = new ModifyComponentStateCheckIntervalsDialog(componentStateCheckIntervals);
    connect(dialog, SIGNAL(confirmButtonClicked(QList<int>)), this, SLOT(modifyComponentStateCheckIntervals(QList<int>)));
    dialog->show();
}

void StatusPushButton::modifyComponentStateCheckIntervals(QList<int> newIntervals)
{
    componentStateCheckIntervals = newIntervals;
    emit componentStateCheckIntervalsChanged();
}

void StatusPushButton::receiveComponentCheckSignal(bool status)
{
    setIcon(QIcon(status ? ":/status_green" : ":/status_red"));
}
