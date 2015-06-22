#ifndef _WAIT_ORDER_H
#define _WAIT_ORDER_H

#include "device/orders/IDeviceOrder.h"

namespace device_emulator {

/*!
    \class Represents an order for waiting some milliseconds
*/
class WaitOrder : public IDeviceOrder
{
public:
    WaitOrder(const unsigned int milliseconds);
    bool Execute(const DeviceBehaviourPtr &context);
    IDeviceOrderPtr Clone() const;
private:
    unsigned int _milliseconds;
};

} // namespace

#endif
