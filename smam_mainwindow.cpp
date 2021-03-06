﻿#include <QDebug>

#include "smam_mainwindow.h"
#include "ui_smam_mainwindow.h"

#include "systemmanager_widget.h"

SMAMMainWindow::SMAMMainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::SMAMMainWindow)
{
	ui->setupUi(this);
    ui->systemManagerAction->setEnabled(true);
    this->setFixedSize(1440, 960);

    SystemManagerWidget* managerWidget = new SystemManagerWidget(this);
    connect(managerWidget, SIGNAL(closeMessage()), this, SLOT(handleManagerCloseMessage()));

    systemManagerSub = ui->mdiArea->addSubWindow(managerWidget);
    systemManagerSub->setSystemMenu(0);
    systemManagerSub->setWindowFlags(systemManagerSub->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
	systemManagerSub->setWindowTitle(tr("系统管理"));
    //systemManagerSub->resize(1280, 760);
    systemManagerSub->setGeometry(0, 0, 1280, 760);
    systemManagerSub->setFixedSize(1280, 760);
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
