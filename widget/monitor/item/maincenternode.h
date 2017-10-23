#ifndef MAINCENTERNODE_H
#define MAINCENTERNODE_H

#include "basenode.h"
#include "bean/main_center.h"

class MainCenterNode : public QObject, public BaseNode
{
    Q_OBJECT

public:
    MainCenterNode(MainCenter* center, quint8 length);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
    MainCenter* center;
};

#endif // MAINCENTERNODE_H
