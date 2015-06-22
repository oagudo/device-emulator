#ifndef _SEND_ORDER_H
#define _SEND_ORDER_H

#include "device/orders/IDeviceOrder.h"
#include "data/Message.h"

namespace device_emulator {

/*!
    \class Represents an order for sending a message
*/
class SendOrder : public IDeviceOrder
{
public:
    SendOrder(const Message &msg);
    bool Execute(const DeviceBehaviourPtr &context);
    IDeviceOrderPtr Clone() const;
private:
    Message _msg;
};

} // namespace

#endif
