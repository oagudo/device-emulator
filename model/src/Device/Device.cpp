#include "Device/Device.h"

namespace device_emulator {

void Device::AddBehaviour(const DeviceBehaviourPtr &behaviour) {
    _behaviours.push_back(behaviour);
}

void Device::Start() {
    std::vector< DeviceBehaviourPtr >::iterator it;
    for (it = _behaviours.begin(); it != _behaviours.end(); ++it) {
        (*it)->Start();
    }
}

void Device::Stop() {
    std::vector< DeviceBehaviourPtr >::iterator it;
    for (it = _behaviours.begin(); it != _behaviours.end(); ++it) {
        (*it)->Stop();
    }
}

} // namespace
