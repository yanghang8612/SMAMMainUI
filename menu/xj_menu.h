/**
 * Title: XJMenu
 * Description: Definition of class XJMenu
 * Copyright: Copyright 2016 CSNO•TARC
 * author：Yang Hang
 * version：1.0
 * modify:
 */

#ifndef SMAM_XJMENU_H
#define SMAM_XJMENU_H

#include <QMainWindow>

#include "base_menu.h"

class XJMenu : public BaseMenu
{
	Q_OBJECT

public:
	XJMenu(QMainWindow* mainWindow);

private slots:
	void quitSystem();
	void showAddStationDialog();
	void showAddReceiverDialog();

private:
	void createMenus();
	void createActions();
	void addAllActionsToMenuBar();
};

#endif // SMAM_XJMENU_H
