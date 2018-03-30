#ifndef MONITORNODE_H
#define MONITORNODE_H

#include "basenode.h"
#include "datastatenode.h"
#include "bean/monitor_station.h"
#include "widget/popup/datatransferstate_frame.h"

class MonitorNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    MonitorNode(MonitorStation* station, quint8 length, DataTransferStateFrame* stateWidget, QWidget* parent);
    ~MonitorNode();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    MonitorStation* getStation() const;
    void updateStateNode();

signals:
    void stationCountChanged(bool isOnline);
    void stationStateChanged(int memID);

public slots:
    void connected(int memID, int centerID, bool isMaster);
    void disconnected(int memID);
    void receivedData(int memID, long length);
    void handleNoData(int memID);

private:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    bool isUsingStateWidget;
    bool isConnected;
    int centerID;
    bool isMaster;
    long rcvdDataLength;
    QString stationName;
    MonitorStation* station;
    DataTransferStateFrame* stateWidget;
    DataStateNode* stateNode;
};

#endif // MONITORNODE_H
