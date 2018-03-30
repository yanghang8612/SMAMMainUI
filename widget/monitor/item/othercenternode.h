#ifndef OTHERCENTERNODE_H
#define OTHERCENTERNODE_H

#include "basenode.h"
#include "bean/other_center.h"
#include "datastatenode.h"

class OtherCenterNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    OtherCenterNode(OtherCenter* center, quint8 length, QWidget* parent);
    ~OtherCenterNode();

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    OtherCenter* getCenter() const;
    void updateStateNode();
    void clearEdge();

public slots:
    void connected(int centerID);
    void disconnected(int centerID);

private:
    QString centerName;
    OtherCenter* center;
    DataStateNode* stateNode;
};

#endif // OTHERCENTERNODE_H
