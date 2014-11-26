#include "Device/Behaviour/DeviceBehaviour.h"
#include "Device/Behaviour/States/NotStartedState.h"
#include "Device/Behaviour/States/ErrorState.h"
#include "Device/Orders/OrderList.h"
#include "Log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.device.behaviour")

DeviceBehaviour::DeviceBehaviour(const std::string &name, const ComChannelPtr &channel, const OrderListPtr &orders) : _name(name), _channel(channel), _orders(orders) {
    TransitionTo(DeviceBehaviourStatePtr(new NotStartedState()));
}

DeviceBehaviourStatePtr DeviceBehaviour::GetState() const {
    return _state;
}

void DeviceBehaviour::Wait() {
     LOG_INFO(logger, "Waiting for behaviour " << GetName() << " to finish");
     _behaviourThread.join();
     LOG_INFO(logger, "Behaviour " << GetName() << " finished!");
}

void DeviceBehaviour::Start() {
    _state->Start(shared_from_this());
    _behaviourThread = boost::thread(&DeviceBehaviour::executeOrders, this);
}

void DeviceBehaviour::Stop() {
    LOG_INFO(logger, "Behaviour " << GetName() << " stopped!");
    _state->Stop(shared_from_this());
    _behaviourThread.join();
}

void DeviceBehaviour::OnMessageArrived(const IMessagePtr &msg) {
    LOG_INFO(logger, "Behaviour " << GetName() << " is notified for message '" << msg->GetId() << "' arrival");
    boost::mutex::scoped_lock lock(_mutexCondition);
    _msgReceived = msg;
    _condition.notify_one();
}

void DeviceBehaviour::WaitForMessageReception(const unsigned int milliseconds) {
    boost::system_time const timeout =
        boost::get_system_time() + boost::posix_time::milliseconds(milliseconds);

    boost::mutex::scoped_lock lock(_mutexCondition);

    if (_condition.timed_wait(lock,timeout) == true) {
        LOG_INFO(logger, "Behaviour " << GetName() << " received message '" << _msgReceived->GetId() << "'");
    }
    else {
        LOG_INFO(logger, "Timeout [" << milliseconds << " ms] triggered because behaviour " <<
                 GetName() << " did not receive any message");
        TransitionTo(DeviceBehaviourStatePtr(new ErrorState("Timeout when waiting for message")));
    }
}

ComChannelPtr DeviceBehaviour::GetCommChannel() {
    return _channel;
}

void DeviceBehaviour::TransitionTo(const DeviceBehaviourStatePtr &newState) {
    _state = newState;
}

void DeviceBehaviour::executeOrders() {
    _state->ExecuteOrders(shared_from_this());
}

} // namespace
