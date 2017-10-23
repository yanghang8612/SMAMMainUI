#ifndef DRAGGABLELISTWIDGET_H
#define DRAGGABLELISTWIDGET_H

#include <QListWidget>

class DraggableListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit DraggableListWidget(QWidget* parent = 0);

signals:
    void dragCompleted();

protected:
    void dropEvent(QDropEvent* event);
};

#endif // DRAGGABLELISTWIDGET_H
