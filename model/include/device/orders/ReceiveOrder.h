#ifndef _RECEIVE_ORDER_H
#define _RECEIVE_ORDER_H

#include "device/orders/IDeviceOrder.h"

namespace device_emulator {

/*!
    \class Represents an order for receiving a message
*/
class ReceiveOrder : public IDeviceOrder
{
public:
    ReceiveOrder(const unsigned int msgID, const unsigned int timeout);
    void Execute(const DeviceBehaviourPtr &context);

private:
    unsigned int _msgID;
    unsigned int _timeout;
};

} // namespace

#endif
