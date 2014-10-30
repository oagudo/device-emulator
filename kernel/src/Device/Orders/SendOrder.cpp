#include "Device/Orders/SendOrder.h"

namespace device_emulator {

SendOrder::SendOrder(const IMessagePtr &msg) : _msg(msg) {
}

void SendOrder::Execute(const IDeviceBehaviourPtr &context) {
    context->GetCommChannel()->Send(_msg);
}

} // namespace
