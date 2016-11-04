#include "smammainwindow.h"
#include "ui_smammainwindow.h"

SMAMMainWindow::SMAMMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SMAMMainWindow)
{
    ui->setupUi(this);
}

SMAMMainWindow::~SMAMMainWindow()
{
    delete ui;
}
