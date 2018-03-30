#ifndef DATASTATENODE_H
#define DATASTATENODE_H

#include <QFrame>

class DataStateNode : public QFrame
{
    Q_OBJECT

public:
    DataStateNode(QWidget *parent = 0);
    void flickerOnce();
    void setState(int state);

    //virtual QRectF boundingRect() const;
    //virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

protected:
    void paintEvent(QPaintEvent* event);

private slots:
    void turnIntoNormal();

private:
    QColor brushColor;
};

#endif // DATASTATENODE_H
