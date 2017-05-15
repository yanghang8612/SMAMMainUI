#ifndef STATIONINFO_WIDGET_H
#define STATIONINFO_WIDGET_H

#include <QTabWidget>

#include "bean/station/standard_station.h"
#include "other_component_header.h"

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

protected:
    void timerEvent(QTimerEvent* event);

private:
	Ui::StationInfoWidget *ui;
	StandardStation* station;
    ReceiverState receiverState[RECEIVER_SHAREDBUFFER_MAXITEMCOUNT];
};

#endif // STATIONINFO_WIDGET_H
