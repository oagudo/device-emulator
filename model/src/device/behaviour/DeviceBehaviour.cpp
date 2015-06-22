#include "device/behaviour/DeviceBehaviour.h"
#include "device/behaviour/states/NotStartedState.h"
#include "device/behaviour/states/ErrorState.h"
#include "device/orders/IOrderList.h"
#include "log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.device.behaviour")

DeviceBehaviour::DeviceBehaviour(const std::string &name, const ComChannelPtr &channel,
                                 const IOrderList &orders) : _name(name), _channel(channel),
                                                             _orders(*(orders.Clone())),
                                                             _state(NotStartedState::Instance()) {
}

DeviceBehaviour::~DeviceBehaviour() { }

DeviceBehaviourStatePtr DeviceBehaviour::GetState() const {
    return _state;
}

void DeviceBehaviour::Wait() {
    _state->Wait(shared_from_this());
}

void DeviceBehaviour::Start() {
    _state->Start(shared_from_this());
}

void DeviceBehaviour::createExecutionThread() {
    _behaviourThread = boost::thread(&DeviceBehaviour::executeOrders, this);
}

void DeviceBehaviour::waitExecutionThread() {
     LOG_DEBUG(logger, "Waiting for behaviour " << GetName() << " to finish");
     _behaviourThread.join();
     LOG_DEBUG(logger, "Behaviour " << GetName() << " finished!");
}

void DeviceBehaviour::Stop() {
    LOG_INFO(logger, "Behaviour " << GetName() << " stopped!");
    _state->Stop(shared_from_this());
}

ComChannelPtr DeviceBehaviour::GetCommChannel() {
    return _channel;
}

std::string DeviceBehaviour::GetName() const { 
    return _name; 
}

IOrderList& DeviceBehaviour::GetOrders() { 
    return _orders;
}

void DeviceBehaviour::executeOrders() {
    _state->ExecuteOrders(shared_from_this());
}

void DeviceBehaviour::transitionTo(const DeviceBehaviourStatePtr &newState) {
    LOG_INFO(logger, "Behaviour " << GetName() << " changing from " <<
                     _state->ToString() << " state to " << newState->ToString() << " state");
    _state = newState;
    newState->Enter(shared_from_this());
}

} // namespace
