#ifndef STATIONINFO_WIDGET_H
#define STATIONINFO_WIDGET_H

#include <QTabWidget>

namespace Ui {
	class StationInfoWidget;
}

class StationInfoWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit StationInfoWidget(QWidget *parent = 0);
	~StationInfoWidget();

private:
	Ui::StationInfoWidget *ui;
};

#endif // STATIONINFO_WIDGET_H
