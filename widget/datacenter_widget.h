#ifndef DATACENTER_WIDGET_H
#define DATACENTER_WIDGET_H

#include <QTabWidget>

#include "bean/data_center.h"

namespace Ui {
    class DataCenterWidget;
}

class DataCenterWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit DataCenterWidget(QWidget *parent = 0);
    ~DataCenterWidget();

    void setDataCenter(DataCenter* dataCenter);

private:
    Ui::DataCenterWidget *ui;
};

#endif // DATACENTER_WIDGET_H
