#include "Device/Behaviour/DeviceBehaviour.h"
#include "Device/Behaviour/States/FinishedState.h"
#include "Device/Behaviour/States/ErrorState.h"
#include "Device/Behaviour/States/StoppedState.h"
#include "Device/Orders/OrderList.h"
#include "Log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.device.behaviour")

DeviceBehaviour::DeviceBehaviour(const std::string &name, const ComChannelPtr &channel, const OrderListPtr &orders) : IDeviceBehaviour(name, channel, orders) { 
}

IDeviceBehaviourStatePtr DeviceBehaviour::GetState() { 
    return _state; 
}

void DeviceBehaviour::Wait() {
    LOG_INFO(logger, "Waiting for behaviour " << GetName() << " to finish");
    _behaviourThread.join();
    LOG_INFO(logger, "Behaviour " << GetName() << " finished!");
}

void DeviceBehaviour::Start() {
    _behaviourThread = boost::thread(&DeviceBehaviour::behave, this);
}

void DeviceBehaviour::Stop() {
    LOG_INFO(logger, "Behaviour " << GetName() << " stopped!");
    _state.reset(new StoppedState());
}

void DeviceBehaviour::OnMessageArrived(const IMessagePtr &msg) {
    LOG_INFO(logger, "Behaviour " << GetName() << " is notified for message '" << 
             msg->GetId() << "' arrival");
    boost::mutex::scoped_lock lock(_mutexCondition);
    _msgReceived = msg;
    _condition.notify_one();
}

void DeviceBehaviour::WaitForMessageReception(const unsigned int milliseconds) {
    boost::system_time const timeout =
        boost::get_system_time() + boost::posix_time::milliseconds(milliseconds);

    boost::mutex::scoped_lock lock(_mutexCondition);

    if (_condition.timed_wait(lock,timeout) == true) {
        LOG_INFO(logger, "Behaviour " << GetName() << " received message '" << 
                 _msgReceived->GetId() << "'");
    }
    else {
        LOG_INFO(logger, "Timeout [" << milliseconds << " ms] triggered because behaviour " << 
                 GetName() << " did not receive any message");
        _state.reset(new ErrorState("Timeout when waiting for message"));
    }
}

ComChannelPtr DeviceBehaviour::GetCommChannel() {
    return _channel;
}

void DeviceBehaviour::behave() {
    while (!_orders->Empty() && _state->AllowToContinue()) {
        _orders->Next()->Execute(shared_from_this());
    }

    // Check if there were some errors
    if (!_state->IsErrorState()) {
        _state.reset(new FinishedState());
    }
}

} // namespace
