#include <QDebug>

#include "status_pushbutton.h"
#include "widget/dialog/componentstatecheckintervals_edit_dialog.h"

StatusPushButton::StatusPushButton(const QIcon& icon, const QString& text, QWidget* parent) :
    QPushButton(icon, text, parent)
{
	this->setStyleSheet("QPushButton{border-style:none}");
    statusFrame = new SoftwareStatusFrame(this);
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
    ComponentStateCheckIntervalsEditDialog* dialog = new ComponentStateCheckIntervalsEditDialog(this);
    dialog->show();
}

void StatusPushButton::receiveComponentCheckSignal(bool status)
{
    setIcon(QIcon(status ? ":/status_green" : ":/status_red"));
}
