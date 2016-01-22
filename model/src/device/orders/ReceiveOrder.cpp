#include <boost/make_shared.hpp>
#include "device/orders/ReceiveOrder.h"
#include "comms/CommunicationChannel.h"
#include "device/behaviour/DeviceBehaviour.h"
#include "log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.device.behaviour.orders.receive")

namespace {
    inline boost::posix_time::ptime Now() {
        return boost::get_system_time();
    }
}

ReceiveOrder::ReceiveOrder(const unsigned int msgID, const unsigned int timeout) :
                           _msgID(msgID), _timeout(timeout) {
}

ReceiveOrder::ReceiveOrder(const ReceiveOrder& other)
{
   _msgID = other._msgID;
   _timeout = other._timeout;
   _msgReceived = boost::none;
}

const ReceiveOrder& ReceiveOrder::operator=(const ReceiveOrder& other)
{
   if (this == &other)
      return *this;
   _msgID = other._msgID;
   _timeout = other._timeout;
   _msgReceived = boost::none;
   return *this;
}


bool ReceiveOrder::Execute(const DeviceBehaviourPtr &context) {
    bool msgReceived = false;

    auto callback = [this, &context] (const Message &msg) {
        this->onMessageArrived(context, msg);
    };

    if (context->GetCommChannel()->WantMessage(_msgID, callback)) {
        msgReceived = true;
    } else {
        msgReceived = waitForMessageReception(context, _timeout);
    }

    return msgReceived;
}


bool ReceiveOrder::waitForMessageReception(const DeviceBehaviourPtr &context,
                                           const unsigned int milliseconds) {
    bool msgReceived = false;
    const auto timeout = Now() + boost::posix_time::milliseconds(milliseconds);

    boost::mutex::scoped_lock lock(_mutexCondition);

    if (_msgReceived || _receiveMsgCondition.timed_wait(lock,timeout)) {
        LOG_DEBUG(logger, "Behaviour " << context->GetName() << " received message '" <<
                          _msgReceived.get().GetId() << "'");
        msgReceived = true;
    } else {
        LOG_ERROR(logger, "Timeout [" << milliseconds << " ms] triggered because behaviour " <<
                          context->GetName() << " did not receive any message");
    }
    return msgReceived;
}

void ReceiveOrder::onMessageArrived(const DeviceBehaviourPtr &context,
                                    const Message &msg) {
    LOG_DEBUG(logger, "Behaviour " << context->GetName() << " is notified for message '" <<
                      msg.GetId() << "' arrival");
    boost::mutex::scoped_lock lock(_mutexCondition);
    _msgReceived = msg;
    _receiveMsgCondition.notify_one();
}

IDeviceOrderPtr ReceiveOrder::Clone() const {
    return boost::make_shared<ReceiveOrder>(*this);
}

} // namespace
