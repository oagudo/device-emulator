#include "device/behaviour/states/ErrorState.h"

namespace device_emulator {

ErrorState::ErrorState() { }

DeviceBehaviourStatePtr ErrorState::Instance() {
    static DeviceBehaviourStatePtr instance(new ErrorState());
    return instance;
}

std::string ErrorState::ToString() const {
    return "Error";
}

} // namespace
