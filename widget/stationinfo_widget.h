#ifndef STATIONINFO_WIDGET_H
#define STATIONINFO_WIDGET_H

#include <QTabWidget>

#include "bean/station/standard_station.h"

namespace Ui {
	class StationInfoWidget;
}

class StationInfoWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit StationInfoWidget(QWidget *parent = 0);
	~StationInfoWidget();

	void setStation(StandardStation* station);

private:
	Ui::StationInfoWidget *ui;
	StandardStation* station;
};

#endif // STATIONINFO_WIDGET_H
