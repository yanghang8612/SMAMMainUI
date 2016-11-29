/**
 * Title: BaseMenu
 * Description: Implementation of class BaseMenu
 * Copyright: Copyright 2016 CSNO•TARC
 * author：Yang Hang
 * version：1.0
 * modify:
 */

#include <QDebug>

#include "base_menu.h"

BaseMenu::BaseMenu(QMainWindow* mainWindow) :
	mainWindow(mainWindow)
{
}

QMenu* BaseMenu::getMenuByName(const QString& menuName)
{
	if (menus.contains(menuName)) {
		return menus[menuName];
	}
	else {
		return 0;
	}
}

void BaseMenu::createHelpMenu()
{
    QAction* helpAction = createAction(tr("帮助"));
	helpAction->setShortcut(QKeySequence::HelpContents);
	helpAction->setStatusTip(tr("获取关于本软件的帮助信息"));
	connect(helpAction, SIGNAL(triggered(bool)), this, SLOT(showHelp()));

    QAction* aboutAction = createAction(tr("关于"));
	aboutAction->setShortcut(QKeySequence::WhatsThis);
	aboutAction->setStatusTip(tr("关于本软件的版本及授权"));
	connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(showAboutPage()));

    createMenu(tr("帮助"));

    addActionToMenu(tr("帮助"), tr("帮助"));
    addActionToMenu(tr("帮助"), tr("关于"));
}

void BaseMenu::showHelp()
{
	qDebug() << "Help clicked";
	//Todo
}

void BaseMenu::showAboutPage()
{
	qDebug() << "About clicked";
	//Todo
}

QAction* BaseMenu::createAction(const QString& actionName)
{
	QAction* action = new QAction(actionName, this);
	actions.insert(actionName, action);
	return action;
}

void BaseMenu::createMenu(const QString& menuName)
{
	QMenu* menu = mainWindow->menuBar()->addMenu(menuName);
	menus.insert(menuName, menu);
}


bool BaseMenu::addActionToMenu(const QString& menuName, const QString& actionName)
{
	if (menus.contains(menuName)) {
		QMenu* addedMenu = menus[menuName];
		if (actions.contains(actionName)) {
			QAction* addedAction = actions[actionName];
			addedMenu->addAction(addedAction);
			return true;
		}
	}
	return false;
}
