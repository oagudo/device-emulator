#include <boost/make_shared.hpp>
#include "device/orders/SendOrder.h"
#include "comms/CommunicationChannel.h"
#include "device/behaviour/DeviceBehaviour.h"

namespace device_emulator {

SendOrder::SendOrder(const Message &msg) : _msg(msg) {
}

bool SendOrder::Execute(const DeviceBehaviourPtr &context) {
    return context->GetCommChannel()->Send(_msg);
}

IDeviceOrderPtr SendOrder::Clone() const {
    return boost::make_shared<SendOrder>(*this);
}

} // namespace
