#include "device/behaviour/states/RunningState.h"
#include "device/behaviour/states/FinishedState.h"
#include "device/behaviour/states/StoppedState.h"
#include "device/orders/IDeviceOrder.h"
#include "device/orders/IOrderList.h"

namespace device_emulator {

RunningState::RunningState() {}

DeviceBehaviourStatePtr RunningState::Instance() {
    static DeviceBehaviourStatePtr instance(new RunningState());
    return instance;
}

std::string RunningState::ToString() const {
    return "Running";
}

void RunningState::Enter(const DeviceBehaviourPtr &context) const {
    createExecutionThread(context);
}

void RunningState::ExecuteOrders(const DeviceBehaviourPtr &context) const {
    while (!context->GetOrders().Empty() &&
           (context->GetState() == RunningState::Instance())) {
        context->GetOrders().Next()->Execute(context);
    }

    if (context->GetState() == RunningState::Instance()) {
        transitionTo(context, FinishedState::Instance());
    }
}

void RunningState::Stop(const DeviceBehaviourPtr &context) const {
    transitionTo(context, StoppedState::Instance());
}

void RunningState::Wait(const DeviceBehaviourPtr &context) const {
    waitExecutionThread(context);
}

} // namespace
