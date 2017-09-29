#ifndef IGMASSTATIONINFO_WIDGET_H
#define IGMASSTATIONINFO_WIDGET_H

#include <QTabWidget>

#include "bean/igmas_station.h"

namespace Ui {
class iGMASStationInfoWidget;
}

class iGMASStationInfoWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit iGMASStationInfoWidget(QWidget *parent = 0);
    ~iGMASStationInfoWidget();

    void setStation(iGMASStation* station);

private:
    Ui::iGMASStationInfoWidget *ui;
    iGMASStation* station;
};

#endif // IGMASSTATIONINFO_WIDGET_H
