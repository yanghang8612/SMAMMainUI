#ifndef IGMASDATACENTER_WIDGET_H
#define IGMASDATACENTER_WIDGET_H

#include <QTabWidget>

#include "bean/igmas_datacenter.h"

namespace Ui {
class iGMASDataCenterWidget;
}

class iGMASDataCenterWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit iGMASDataCenterWidget(QWidget *parent = 0);
    ~iGMASDataCenterWidget();

    void setDataCenter(iGMASDataCenter* dataCenter);

private:
    Ui::iGMASDataCenterWidget *ui;
};

#endif // IGMASDATACENTER_WIDGET_H
