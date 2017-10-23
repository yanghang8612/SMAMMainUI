#ifndef MAINCENTER_H
#define MAINCENTER_H

#include <QString>
#include <QList>

#include "other_center.h"

class MainCenter
{
public:
    MainCenter();

    void addOtherCenter(OtherCenter* otherCenter);
    QList<OtherCenter*> getOtherCenters() const;

    QString getCenterName() const;
    void setCenterName(const QString& value);

    QString getDetail() const;
    void setDetail(const QString& value);

private:
    QString centerName;
    QString detail;
    QList<OtherCenter*> otherCenters;
};

#endif // MAINCENTER_H
