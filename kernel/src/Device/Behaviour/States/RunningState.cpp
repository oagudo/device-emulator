#include "Device/Behaviour/States/RunningState.h"

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
    while (!context->GetOrders()->Empty() &&
           (context->GetState().get() == this)) {
        context->GetOrders()->Next()->Execute(context);
    }

    if (context->GetState().get() == this) {
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
