#include "Device/Device.h"

namespace device_emulator {

void Device::AddBehaviour(const IDeviceBehaviourPtr &behaviour) {
    _behaviours.push_back(behaviour);
}

} // namespace
