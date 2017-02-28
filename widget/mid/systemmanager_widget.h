#ifndef SYSTEMMANAGER_WIDGET_H
#define SYSTEMMANAGER_WIDGET_H

#include <QWidget>
#include <unistd.h>

#include "common.h"
#include "utilies/cpumem_info.h"
#include "utilies/shared_buffer.h"
#include "widget/treewidget/smam_treewidget.h"
#include "widget/statuspopup/status_pushbutton.h"

namespace Ui {
	class SystemManagerWidget;
}

class SystemManagerWidget : public QWidget
{
	Q_OBJECT

public:
    explicit SystemManagerWidget(DeploymentType::Value type = DeploymentType::XJ_CENTER, QWidget* parent = 0);
	~SystemManagerWidget();

protected:
	void timerEvent(QTimerEvent* event);

private slots:
	void addMessageToInfoContainer();
    void closeEvent(QCloseEvent* closeEvent);

signals:
    void closeMessage();

public:
	SMAMTreeWidget* treeWidget;

private:
	Ui::SystemManagerWidget *ui;
    QWidget* contentWidget;
    StatusPushButton* softwareStatus;
    int timerID;
    SharedBuffer* messageBuffers[COMPONENT_COUNT];
};

#endif // SYSTEMMANAGER_WIDGET_H
