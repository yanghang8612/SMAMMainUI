#ifndef STATIONINFO_WIDGET_H
#define STATIONINFO_WIDGET_H

#include <QTabWidget>

#include "bean/station/standard_station.h"

namespace Ui {
	class StationInfoWidget;
}

class StandardStationInfoWidget : public QTabWidget
{
	Q_OBJECT

public:
    explicit StandardStationInfoWidget(QWidget *parent = 0);
    ~StandardStationInfoWidget();

	void setStation(StandardStation* station);

private:
	Ui::StationInfoWidget *ui;
	StandardStation* station;
};

#endif // STATIONINFO_WIDGET_H
