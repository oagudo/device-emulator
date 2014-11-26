#ifndef _WAIT_ORDER_H
#define _WAIT_ORDER_H

#include "Device/Orders/IDeviceOrder.h"

namespace device_emulator {

/*!
    \class Represents an order for waiting some milliseconds
*/
class WaitOrder : public IDeviceOrder
{
public:
    WaitOrder(const unsigned int milliseconds);
    void Execute(const DeviceBehaviourPtr &context);

private:
    unsigned int _milliseconds;
};

} // namespace

#endif
