#include "status_pushbutton.h"

StatusPushButton::StatusPushButton(const QIcon& icon, const QString& text, QWidget* parent) :
    QPushButton(icon, text, parent)
{
	this->setStyleSheet("QPushButton{border-style:none}");
    statusFrame = new SoftwareStatusFrame(parent);
    statusFrame->setStyleSheet(QString("QFrame{border: 1px solid gray;background-color: white;}QPushButton {border-style: none;font: 12px;}"));
    statusFrame->hide();
    connect(statusFrame, SIGNAL(isEveryComponentNormal(bool)), this, SLOT(receiveComponentCheckSignal(bool)));
}

void StatusPushButton::enterEvent(QEvent*)
{
    statusFrame->setGeometry(this->pos().x() + 150, this->pos().y() + 30, 170, 200);
    statusFrame->show();
}

void StatusPushButton::leaveEvent(QEvent*)
{
    statusFrame->hide();
}

void StatusPushButton::receiveComponentCheckSignal(bool status)
{
    setIcon(QIcon(status ? ":/status_green" : ":/status_red"));
}
