#ifndef IGMASNODE_H
#define IGMASNODE_H

#include "basenode.h"
#include "datastatenode.h"
#include "bean/igmas_station.h"
#include "utilities/shared_buffer.h"
#include "widget/statuspopup/datatransferstate_frame.h"

class iGMASNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    iGMASNode(iGMASStation* station, quint8 length, QWidget* parent);

    QString getStationIPAddress() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private slots:
    void checkDataReceivingState();

private:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    iGMASStation* station;
    DataStateNode* stateNode;
    DataTransferStateFrame* stateWidget;
    QTimer* timer;
    SharedBuffer* dataReceivingSharedBuffer;
};

#endif // IGMASNODE_H
