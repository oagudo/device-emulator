#include "Device/Behaviour/DeviceBehaviour.h"
#include "Device/Behaviour/States/NotStartedState.h"
#include "Device/Behaviour/States/FinishedState.h"
#include "Device/Behaviour/States/ErrorState.h"
#include "Device/Behaviour/States/StoppedState.h"
#include "Device/Orders/OrderList.h"

namespace device_emulator {

DeviceBehaviour::DeviceBehaviour(const ComChannelPtr &channel, const std::string &behaviourName) : 
  _channel(channel), _behaviourName(behaviourName), _state(new NotStartedState()) { 
}

IDeviceBehaviourStatePtr DeviceBehaviour::GetState() { 
    return _state; 
}

void DeviceBehaviour::Wait() {
    _behaviourThread.join();
}

void DeviceBehaviour::Start(OrderListPtr &orders) {
    _behaviourThread = boost::thread(&DeviceBehaviour::behave, this, orders);
}

void DeviceBehaviour::Stop() {
    _state.reset(new StoppedState());
}

void DeviceBehaviour::MessageArrived(const IMessagePtr &msg) {
    // Device behaviour notified!
    boost::mutex::scoped_lock lock(_mutexCondition);
    _condition.notify_one();
    _msgReceived = msg;
}

void DeviceBehaviour::WaitForMessageReception(const unsigned int milliseconds) {
    boost::system_time const timeout =
        boost::get_system_time() + boost::posix_time::milliseconds(milliseconds);

    boost::mutex::scoped_lock lock(_mutexCondition);

    if (_condition.timed_wait(lock,timeout) == true) {
        // Message is ready, take it !!
    }
    else {
        _state.reset(new ErrorState("Timeout when waiting for message"));
    }
}

ComChannelPtr DeviceBehaviour::GetCommChannel()
{
    return _channel;
}

void DeviceBehaviour::behave(OrderListPtr &orders) {
    while (!orders->Empty() && _state->AllowToContinue()) {
        orders->Next()->Execute(shared_from_this());
    }

    // Check if there were some errors
    if (!_state->IsErrorState()) {
        _state.reset(new FinishedState());
    }
}

} // namespace
