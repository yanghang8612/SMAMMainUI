/**
 * Title: XJMenu
 * Description: Implementation of class XJMenu
 * Copyright: Copyright 2016 CSNO•TARC
 * author：Yang Hang
 * version：1.0
 * modify:
 */

#include "xj_menu.h"

XJMenu::XJMenu(QMainWindow* mainWindow) :
	BaseMenu(mainWindow)
{
	createActions();
	createMenus();
	addAllActionsToMenuBar();
	createHelpMenu();
}

void XJMenu::quitSystem()
{
	qDebug() << "Quit clicked";
}

void XJMenu::showAddStationDialog()
{
	qDebug() << "Add station clicked";
}

void XJMenu::showAddReceiverDialog()
{
	qDebug() << "Add receiver clicked";
}

void XJMenu::createMenus()
{
	createMenu(tr("系统"));
	createMenu("基准站管理");
	createMenu("接收机管理");
}

void XJMenu::createActions()
{
	QAction* quitSystemAction = createAction("退出系统");
	connect(quitSystemAction, SIGNAL(triggered(bool)), this, SLOT(quitSystem()));

	QAction* addStationAction = createAction("添加基准站");
	connect(addStationAction, SIGNAL(triggered(bool)), this, SLOT(showAddStationDialog()));

	QAction* addReceiverAction = createAction("添加接收机");
	connect(addReceiverAction, SIGNAL(triggered(bool)), this, SLOT(showAddReceiverDialog()));
}

void XJMenu::addAllActionsToMenuBar()
{
	addActionToMenu("系统", "退出系统");
	addActionToMenu("基准站管理", "添加基准站");
	addActionToMenu("接收机管理", "添加接收机");
}
