#ifndef STATIONINFO_WIDGET_H
#define STATIONINFO_WIDGET_H

#include <QTabWidget>

#include "other_component_header.h"
#include "bean/standard_station.h"

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
    ReceiverState receiverState[RECEIVER_MAXITEMCOUNT];
};

#endif // STATIONINFO_WIDGET_H
