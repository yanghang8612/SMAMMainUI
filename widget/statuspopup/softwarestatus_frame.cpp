#include "softwarestatus_frame.h"
#include "ui_softwarestatus_frame.h"

SoftwareStatusFrame::SoftwareStatusFrame(QWidget *parent) :
	QFrame(parent),
	ui(new Ui::SoftwareStatusFrame)
{
	ui->setupUi(this);
}

SoftwareStatusFrame::~SoftwareStatusFrame()
{
	delete ui;
}
