#include "Device/Behaviour/States/NotStartedState.h"

namespace device_emulator {

NotStartedState::NotStartedState() { }

DeviceBehaviourStatePtr NotStartedState::Instance() {
    static DeviceBehaviourStatePtr instance(new NotStartedState());
    return instance;
}

std::string NotStartedState::ToString() const {
    return "NotStarted";
}

void NotStartedState::Start(const DeviceBehaviourPtr &context) const {
    transitionTo(context, RunningState::Instance());
}

} // namespace
