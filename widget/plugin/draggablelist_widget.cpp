#include <QDropEvent>
#include <QDebug>

#include "draggablelist_widget.h"

DraggableListWidget::DraggableListWidget(QWidget* parent) : QListWidget(parent)
{}

void DraggableListWidget::dropEvent(QDropEvent* event)
{
    QListWidget::dropEvent(event);
    emit dragCompleted();
}

