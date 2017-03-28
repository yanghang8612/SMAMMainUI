#ifndef IGMASNODE_H
#define IGMASNODE_H

#include "basenode.h"
#include "bean/station/igmas_station.h"

class IGMASNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    IGMASNode(IGMASStation* station, quint8 length);

    QString getStationIPAddress() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
    IGMASStation* station;
};

#endif // IGMASNODE_H
