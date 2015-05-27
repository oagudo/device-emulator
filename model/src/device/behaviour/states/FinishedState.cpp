#include "device/behaviour/states/FinishedState.h"

namespace device_emulator {

FinishedState::FinishedState() { }

DeviceBehaviourStatePtr FinishedState::Instance() {
    static DeviceBehaviourStatePtr instance(new FinishedState());
    return instance;
}

std::string FinishedState::ToString() const {
    return "Finished";
}

} // namespace
