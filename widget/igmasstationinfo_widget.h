#ifndef IGMASSTATIONINFO_WIDGET_H
#define IGMASSTATIONINFO_WIDGET_H

#include <QTabWidget>

#include "bean/station/igmas_station.h"

namespace Ui {
class IGMASStationInfoWidget;
}

class IGMASStationInfoWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit IGMASStationInfoWidget(QWidget *parent = 0);
    ~IGMASStationInfoWidget();

    void setStation(IGMASStation* station);

private:
    Ui::IGMASStationInfoWidget *ui;
    IGMASStation* station;
};

#endif // IGMASSTATIONINFO_WIDGET_H
