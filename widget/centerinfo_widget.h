#ifndef USERMANAGER_WIDGET_H
#define USERMANAGER_WIDGET_H

#include <QTabWidget>

#include "bean/center/other_center.h"

namespace Ui {
    class CenterInfoWidget;
}

class CenterInfoWidget : public QTabWidget
{
	Q_OBJECT

public:
    explicit CenterInfoWidget(QWidget *parent = 0);
    ~CenterInfoWidget();

    void setCenter(OtherCenter* value);

private:
    Ui::CenterInfoWidget *ui;
    OtherCenter* center;
};

#endif // USERMANAGER_WIDGET_H
