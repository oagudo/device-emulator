#ifndef _SEND_ORDER_H
#define _SEND_ORDER_H

#include "Device/Orders/IDeviceOrder.h"

namespace device_emulator {

/*!
    \class Represents an order for sending a message
*/
class SendOrder : public IDeviceOrder
{
public:
    SendOrder(const IMessagePtr &msg);
    void Execute(const DeviceBehaviourPtr &context);

private:
    IMessagePtr _msg;
};

} // namespace

#endif
