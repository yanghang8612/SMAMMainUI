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
    Ui::iGMASStationInfoWidget *ui;
    iGMASStation* station;
    QStringList dataCenters;
};

#endif // IGMASSTATIONINFO_WIDGET_H
