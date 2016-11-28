/**
 * Title: BJMenu
 * Description: Definition of class BJMenu
 * Copyright: Copyright 2016 CSNO•TARC
 * author：Yang Hang
 * version：1.0
 * modify:
 */

#ifndef SMAM_BJMENU_H
#define SMAM_BJMENU_H

#include "base_menu.h"

class BJMenu : public BaseMenu
{
	Q_OBJECT

public:
	BJMenu(QMainWindow* mainWindow);

private slots:
	void quitSystem();
	void showAddIGSStationDialog();
	void showAddIGMASStationDialog();

private:
	void createMenus();
	void createActions();
	void addAllActionsToMenuBar();
};

#endif // SMAM_BJMENU_H
