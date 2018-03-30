#include "main_center.h"

MainCenter::MainCenter(const QString& centerName) : centerName(centerName)
{}

void MainCenter::addOtherCenter(OtherCenter* otherCenter)
{
    otherCenters << otherCenter;
}

QList<OtherCenter*> MainCenter::getOtherCenters() const
{
    return otherCenters;
}

QString MainCenter::getCenterName() const
{
    return centerName;
}

void MainCenter::setCenterName(const QString& value)
{
    centerName = value;
}

QString MainCenter::getDetail() const
{
    return detail;
}

void MainCenter::setDetail(const QString& value)
{
    detail = value;
}



