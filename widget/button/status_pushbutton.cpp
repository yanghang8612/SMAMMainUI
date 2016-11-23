#include <QDebug>

#include "status_pushbutton.h"

StatusPushButton::StatusPushButton(const QIcon& icon, const QString& text, QWidget* parent) :
	QPushButton(icon, text, parent)
{
	this->setStyleSheet("QPushButton{border-style:none}");
	statusFrame = new SoftwareStatusFrame();
	statusFrame->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	statusFrame->setFocusPolicy(Qt::NoFocus);
}

void StatusPushButton::enterEvent(QEvent* event)
{
	qDebug() << "enter";
	statusFrame->setGeometry(QCursor::pos().x() + 1, QCursor::pos().y() + 1, 170, 200);
	statusFrame->show();
}

void StatusPushButton::leaveEvent(QEvent* event)
{
	qDebug() << "leave";
	statusFrame->hide();
}

