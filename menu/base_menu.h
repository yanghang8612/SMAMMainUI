/**
 * Title: BaseMenu
 * Description: Definition of class BaseMenu
 * Copyright: Copyright 2016 CSNO•TARC
 * author：Yang Hang
 * version：1.0
 * modify:
 */

#ifndef SMAM_BASEMENU_H
#define SMAM_BASEMENU_H

#include <QtCore>
#include <QtGui>

class BaseMenu : public QObject
{
	Q_OBJECT

public:
	BaseMenu(QMainWindow* mainWindow);
	QMenu* getMenuByName(const QString& menuName);

protected:
	QHash<QString, QAction*> actions;
	QHash<QString, QMenu*> menus;

	virtual void createActions() = 0;
	virtual void createMenus() = 0;
	virtual void addAllActionsToMenuBar() = 0;

	void createHelpMenu();
	QAction* createAction(const QString& actionName);
	void createMenu(const QString& menuName);
	bool addActionToMenu(const QString& menuName, const QString& actionName);

private slots:
	void showHelp();
	void showAboutPage();

private:
	QMainWindow* mainWindow;
};

#endif // SMAM_BASEMENU_H
