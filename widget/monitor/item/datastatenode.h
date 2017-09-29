#ifndef DATASTATENODE_H
#define DATASTATENODE_H

#include <QGraphicsObject>

class DataStateNode : public QGraphicsObject
{
    Q_OBJECT

public:
    DataStateNode();
    void flickerOnce();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private slots:
    void turnIntoNormal();

private:
    Qt::GlobalColor brushColor;
};

#endif // DATASTATENODE_H
