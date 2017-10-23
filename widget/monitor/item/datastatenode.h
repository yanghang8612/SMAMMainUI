#ifndef DATASTATENODE_H
#define DATASTATENODE_H

#include <QGraphicsObject>

class DataStateNode : public QGraphicsObject
{
    Q_OBJECT

public:
    DataStateNode();
    void flickerOnce();
    void setState(int state);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private slots:
    void turnIntoNormal();

private:
    Qt::GlobalColor brushColor;
    Qt::GlobalColor preBrushColor;
};

#endif // DATASTATENODE_H
