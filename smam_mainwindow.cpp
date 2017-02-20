#include "smam_mainwindow.h"
#include "ui_smam_mainwindow.h"
#include "menu/bj_menu.h"
#include "menu/xj_menu.h"
#include "widget/mid/systemmanager_widget.h"

SMAMMainWindow::SMAMMainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::SMAMMainWindow)
{
	ui->setupUi(this);
    ui->systemManagerAction->setEnabled(true);
    this->setFixedSize(1440, 960);

    menu = new XJMenu(this);

    SystemManagerWidget* managerWidget = new SystemManagerWidget((DeploymentType::Value) 1, this);
    connect(managerWidget, SIGNAL(closeMessage()), this, SLOT(handleManagerCloseMessage()));

	systemManagerSub = ui->mdiArea->addSubWindow(managerWidget);
	systemManagerSub->setWindowTitle(tr("系统管理"));
    //systemManagerSub->resize(1280, 760);
    systemManagerSub->setGeometry(0, 0, 1280, 760);
    //systemManagerSub->setFixedSize(1280, 760);
    //systemManagerSub->setWindowModified(false);
    systemManagerSub->setWindowIcon(QIcon(":/manager"));
    systemManagerSub->show();
}

SMAMMainWindow::~SMAMMainWindow()
{
	delete ui;
}

void SMAMMainWindow::handleManagerCloseMessage()
{
    ui->systemManagerAction->setChecked(false);
    systemManagerSub->hide();
}

void SMAMMainWindow::on_systemManagerAction_triggered(bool checked)
{
    if (checked) {
        systemManagerSub->show();
    }
    else {
        systemManagerSub->hide();
    }
}
