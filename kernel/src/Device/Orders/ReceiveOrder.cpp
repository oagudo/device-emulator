#include "Device/Orders/ReceiveOrder.h"

namespace device_emulator {

ReceiveOrder::ReceiveOrder(const unsigned int msgID, const unsigned int timeout) : _msgID(msgID), _timeout(timeout) {
}

void ReceiveOrder::Execute(const DeviceBehaviourPtr &context) {
    if (context->GetCommChannel()->WantMessage(_msgID, context)) {
        // Message was ready to be picked!
    }
    else {
        context->waitForMessageReception(_timeout);
    }
}

} // namespace
