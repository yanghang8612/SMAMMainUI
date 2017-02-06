#ifndef OTHERCENTER_H
#define OTHERCENTER_H

#include "base_center.h"
#include "smam_component_header.h"

class OtherCenter : public BaseCenter
{
public:
    OtherCenter();
    OtherCenterInBuffer toOtherCenterInBuffer();
};

#endif // OTHERCENTER_H
