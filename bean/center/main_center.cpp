#include "main_center.h"

MainCenter::MainCenter()
{}

void MainCenter::addOtherCenter(OtherCenter* otherCenter)
{
    otherCenters << otherCenter;
}
QList<OtherCenter*> MainCenter::getOtherCenters() const
{
    return otherCenters;
}

