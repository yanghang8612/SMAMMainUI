#include "smam_mainwindow.h"
#include "ui_smam_mainwindow.h"
#include "menu/bj_menu.h"
#include "menu/xj_menu.h"
#include "mid/systemmanager_widget.h"
#include "mid/systemmonitor_widget.h"

SMAMMainWindow::SMAMMainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::SMAMMainWindow)
{
	ui->setupUi(this);
	menu = new XJMenu(this);
	SystemManagerWidget* managerWidget = new SystemManagerWidget(this);
	systemManagerSub = ui->mdiArea->addSubWindow(managerWidget);
	systemManagerSub->setWindowTitle(tr("系统管理"));
	systemManagerSub->resize(1280, 760);
	systemManagerSub->setWindowModified(false);
	systemManagerSub->show();

	SystemMonitorWidget* monitorWidget = new SystemMonitorWidget(this, managerWidget->treeWidget);
	systemMonitorSub = ui->mdiArea->addSubWindow(monitorWidget);
	systemMonitorSub->setWindowTitle(tr("系统监控"));
	systemMonitorSub->resize(1280, 760);
	systemMonitorSub->setWindowModified(false);
	systemMonitorSub->show();
}

SMAMMainWindow::~SMAMMainWindow()
{
	delete ui;
}


