#ifndef SHAREDMEMORYINFO_WIDGET_H
#define SHAREDMEMORYINFO_WIDGET_H

#include <QTabWidget>

#include "utilies/shared_buffer.h"

namespace Ui {
class SharedMemoryInfoWidget;
}

class SharedMemoryInfoWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit SharedMemoryInfoWidget(QWidget *parent = 0);
    ~SharedMemoryInfoWidget();

protected:
    void timerEvent(QTimerEvent* event);
    bool eventFilter(QObject* target, QEvent* event);

private slots:
    void on_viewButton_clicked();
    void on_autoUpdateButton_clicked(bool checked);
    void on_memoryHexInfoTable_itemSelectionChanged();
    void on_memoryCharInfoTable_itemSelectionChanged();

private:
    Ui::SharedMemoryInfoWidget *ui;
    void* sharedMemoryPointer;
    SharedBuffer* buffer;
    bool hexTableChanging;
    bool charTableChanging;

    void updateView();

};

#endif // SHAREDMEMORYINFO_WIDGET_H
