#include "device/Device.h"
#include "device/behaviour/DeviceBehaviour.h"

namespace device_emulator {

Device::Device(const std::string &deviceName) : _deviceName(deviceName) { }

void Device::AddBehaviour(const DeviceBehaviourPtr &behaviour) {
    _behaviours.push_back(behaviour);
}

void Device::Start() {
    for (auto &behaviour : _behaviours) {
        behaviour->Start();
    }
}

void Device::Stop() {
    for (auto &behaviour : _behaviours) {
        behaviour->Stop();
    }
}

void Device::Wait() {
    for (auto &behaviour : _behaviours) {
        behaviour->Wait();
    }
}

std::string Device::GetName() const { return _deviceName; }

} // namespace
