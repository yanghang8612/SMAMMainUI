#ifndef SYSTEMMANAGER_WIDGET_H
#define SYSTEMMANAGER_WIDGET_H

#include <QWidget>
#include <QProcess>
#include <unistd.h>
#include <QTextStream>

#include "utilities/shared_buffer.h"
#include "widget/treewidget/smam_treewidget.h"
#include "widget/popup/status_pushbutton.h"

namespace Ui {
	class SystemManagerWidget;
}

class SystemManagerWidget : public QWidget
{
	Q_OBJECT

public:
    explicit SystemManagerWidget(QWidget* parent = 0);
	~SystemManagerWidget();

private slots:
    void checkResource();
    void checkMessage();
    void closeEvent(QCloseEvent* closeEvent);

signals:
    void closeMessage();

private:
	Ui::SystemManagerWidget *ui;

    QTimer* resourceCheckTimer;
    QTimer* messageReceiveTimer;
    SMAMTreeWidget* treeWidget;
    StatusPushButton* softwareStatus;
    QProcess* proc;
    SharedBuffer* messageBuffers[COMPONENT_COUNT];
};

#endif // SYSTEMMANAGER_WIDGET_H
