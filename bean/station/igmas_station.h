#ifndef IGMASSTATION_H
#define IGMASSTATION_H

#include "base_station.h"

class IGMASStation : public BaseStation
{
public:
	IGMASStation();

private:
    quint16 mountPoint;
};

#endif // IGMASSTATION_H
