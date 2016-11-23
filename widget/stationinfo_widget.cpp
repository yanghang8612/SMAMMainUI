#include "stationinfo_widget.h"
#include "ui_stationinfo_widget.h"

StationInfoWidget::StationInfoWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::StationInfoWidget)
{
	ui->setupUi(this);
}

StationInfoWidget::~StationInfoWidget()
{
	delete ui;
}
