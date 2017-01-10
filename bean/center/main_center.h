#ifndef MAINCENTER_H
#define MAINCENTER_H

#include <QList>

#include "other_center.h"

class MainCenter : public BaseCenter
{
public:
    MainCenter();

    void addOtherCenter(OtherCenter* otherCenter);
    QList<OtherCenter*> getOtherCenters() const;

private:
    QList<OtherCenter*> otherCenters;
};

#endif // MAINCENTER_H
