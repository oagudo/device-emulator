#ifndef _STOPPED_STATE_H
#define _STOPPED_STATE_H

#include "DeviceBehaviourState.h"

namespace device_emulator {

class StoppedState : public DeviceBehaviourState {
public:
    static DeviceBehaviourStatePtr Instance();
    std::string ToString() const;
    void Enter(const DeviceBehaviourPtr &context) const;
private:
    StoppedState();
};

} // namespace

#endif
