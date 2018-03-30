#include <QPainter>
#include <QTimer>
#include <QDebug>

#include "datastatenode.h"

DataStateNode::DataStateNode(QWidget* parent) :
    QFrame(parent),
    brushColor(Qt::darkGray)
{
    this->setStyleSheet("QFrame{border: 0px;}");
    this->setAttribute(Qt::WA_PaintOnScreen);
}

void DataStateNode::flickerOnce()
{
    if (brushColor == Qt::white) {
        brushColor = Qt::green;
        update();
        QTimer::singleShot(50, this, SLOT(turnIntoNormal()));
    }
}

void DataStateNode::setState(int state)
{
    switch (state) {
        case 0:
            brushColor = Qt::darkGray;
            break;
        case 1:
            brushColor = Qt::white;
            break;
        case 2:
            brushColor = Qt::red;
            break;
        case 3:
            brushColor = Qt::green;
            break;
    }
    update();
}

void DataStateNode::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(255, 255, 255));
    painter.setPen(Qt::gray);
    painter.setBrush(brushColor);
    painter.drawEllipse(1, 1, 6, 6);
}

void DataStateNode::turnIntoNormal()
{
    brushColor = Qt::white;
    update();
}
