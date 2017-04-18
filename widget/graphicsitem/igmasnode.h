#ifndef IGMASNODE_H
#define IGMASNODE_H

#include "basenode.h"
#include "bean/station/igmas_station.h"
#include "utilies/shared_buffer.h"

class IGMASNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    IGMASNode(IGMASStation* station, quint8 length);

    QString getStationIPAddress() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private slots:
    void checkDataReceivingState();

private:
    IGMASStation* station;
    QTimer* timer;
    SharedBuffer* dataReceivingSharedBuffer;
};

#endif // IGMASNODE_H
