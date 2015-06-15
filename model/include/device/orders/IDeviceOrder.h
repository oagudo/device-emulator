#ifndef _IDEVICE_ORDER_H
#define _IDEVICE_ORDER_H

#include "Common.h"

namespace device_emulator {

/*!
    \class Represents a device order
*/
class IDeviceOrder
{
public:
    virtual void Execute(const DeviceBehaviourPtr &context) = 0;
};

} // namespace

#endif
