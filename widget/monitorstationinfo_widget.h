#ifndef MONITORSTATIONINFO_WIDGET_H
#define MONITORSTATIONINFO_WIDGET_H

#include <QTabWidget>

#include "bean/monitor_station.h"

namespace Ui {
    class MonitorStationInfoWidget;
}

class MonitorStationInfoWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit MonitorStationInfoWidget(QWidget *parent = 0);
    ~MonitorStationInfoWidget();

    void setStation(MonitorStation* station);

signals:
    void dataSourceModified(int memID);
    void dataSourceDeleted(int memID, int centerIndex);

private slots:
    void showRightMenu(QPoint pos);
    void showAddDataCenterDialog();
    void addDataCenter(const QString& newDataCenters);
    void deleteDataCenter();
    void handleDragAction();

private:
    Ui::MonitorStationInfoWidget *ui;
    MonitorStation* station;
    QStringList dataCenters;
};

#endif // MONITORSTATIONINFO_WIDGET_H
