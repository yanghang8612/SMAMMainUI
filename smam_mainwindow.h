#ifndef SMAM_MAINWINDOW_H
#define SMAM_MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <unistd.h>

#include "menu/base_menu.h"
#include "utilies/cpumem_info.h"
#include "widget/button/status_pushbutton.h"

namespace Ui {
class SMAMMainWindow;
}

class SMAMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMAMMainWindow(QWidget *parent = 0);
    ~SMAMMainWindow();

protected:
	void timerEvent(QTimerEvent* event);

private:
	Ui::SMAMMainWindow *ui;
	BaseMenu* menu;
	QWidget* contentWidget;
	int timerID;

	StatusPushButton* softwareStatus;
	StatusPushButton* otherCentreStatus;

private slots:
	void addMessageToInfoContainer();
};

#endif // SMAM_MAINWINDOW_H
