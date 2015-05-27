#include "device/behaviour/states/StoppedState.h"

namespace device_emulator {

StoppedState::StoppedState() { }

DeviceBehaviourStatePtr StoppedState::Instance() {
    static DeviceBehaviourStatePtr instance(new StoppedState());
    return instance;
}

std::string StoppedState::ToString() const {
    return "Stopped";
}

void StoppedState::Enter(const DeviceBehaviourPtr &context) const {
    waitExecutionThread(context);
}

} // namespace
