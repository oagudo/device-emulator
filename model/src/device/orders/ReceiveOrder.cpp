#include "device/orders/ReceiveOrder.h"
#include "comms/CommunicationChannel.h"
#include "device/behaviour/DeviceBehaviour.h"

namespace device_emulator {

ReceiveOrder::ReceiveOrder(const unsigned int msgID, const unsigned int timeout) :
                           _msgID(msgID), _timeout(timeout) {
}

bool ReceiveOrder::Execute(const DeviceBehaviourPtr &context) {

    auto callback = [&context] (const Message &msg) {
        context->onMessageArrived(msg);
    };

    if (context->GetCommChannel()->WantMessage(_msgID, callback)) {
        // Message was ready to be picked!
    }
    else {
        context->waitForMessageReception(_timeout);
    }

    return true;
}

} // namespace
