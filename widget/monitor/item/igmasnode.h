#ifndef IGMASNODE_H
#define IGMASNODE_H

#include "basenode.h"
#include "datastatenode.h"
#include "bean/igmas_station.h"
#include "widget/popup/datatransferstate_frame.h"

class iGMASNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    iGMASNode(iGMASStation* station, quint8 length, QWidget* parent);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

public slots:
    void connected(int memID, int centerID, bool isMaster);
    void disconnected(int memID);
    void receivedData(int memID);

private:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    bool isConnected;
    iGMASStation* station;
    DataStateNode* stateNode;
    DataTransferStateFrame* stateWidget;
};

#endif // IGMASNODE_H
