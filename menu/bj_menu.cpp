/**
 * Title: BJMenu
 * Description: Implementation of class BJMenu
 * Copyright: Copyright 2016 CSNO•TARC
 * author：Yang Hang
 * version：1.0
 * modify:
 */

#include <QDebug>

#include "bj_menu.h"

BJMenu::BJMenu(QMainWindow* mainWindow) :
	BaseMenu(mainWindow)
{
	createActions();
	createMenus();
	addAllActionsToMenuBar();
	createHelpMenu();
}

void BJMenu::quitSystem()
{
	qDebug() << "Quit clicked";
	//Todo
}

void BJMenu::showAddIGSStationDialog()
{
	qDebug() << "Add iGS station clicked";
}

void BJMenu::showAddIGMASStationDialog()
{
	qDebug() << "Add iGMAS station clicked";
}

void BJMenu::createMenus()
{
	createMenu("系统");
	createMenu("IGS站管理");
	createMenu("IGMAS站管理");
}

void BJMenu::createActions()
{
	QAction* quitSystemAction = createAction("退出系统");
	connect(quitSystemAction, SIGNAL(triggered(bool)), this, SIGNAL(quitSystem()));

	QAction* addIGSStationAction = createAction("添加IGS站");
	connect(addIGSStationAction, SIGNAL(triggered(bool)), this, SIGNAL(showAddIGSStationDialog()));

	QAction* addIGMASStationAction = createAction("添加IGMAS站");
	connect(addIGMASStationAction, SIGNAL(triggered(bool)), this, SIGNAL(showAddIGMASStationDialog()));
}

void BJMenu::addAllActionsToMenuBar()
{
	addActionToMenu("系统", "退出系统");
	addActionToMenu("IGS站管理", "添加IGS站");
	addActionToMenu("IGMAS站管理", "添加IGMAS站");
}
