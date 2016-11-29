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
    createMenu(tr("系统"));
    createMenu(tr("IGS站管理"));
    createMenu(tr("IGMAS站管理"));
}

void BJMenu::createActions()
{
    QAction* quitSystemAction = createAction(tr("退出系统"));
	connect(quitSystemAction, SIGNAL(triggered(bool)), this, SIGNAL(quitSystem()));

    QAction* addIGSStationAction = createAction(tr("添加IGS站"));
	connect(addIGSStationAction, SIGNAL(triggered(bool)), this, SIGNAL(showAddIGSStationDialog()));

    QAction* addIGMASStationAction = createAction(tr("添加IGMAS站"));
	connect(addIGMASStationAction, SIGNAL(triggered(bool)), this, SIGNAL(showAddIGMASStationDialog()));
}

void BJMenu::addAllActionsToMenuBar()
{
    addActionToMenu(tr("系统"), tr("退出系统"));
    addActionToMenu(tr("IGS站管理"), tr("添加IGS站"));
    addActionToMenu(tr("IGMAS站管理"), tr("添加IGMAS站"));
}
