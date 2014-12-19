#ifndef _STOPPED_STATE_H
#define _STOPPED_STATE_H

#include "DeviceBehaviourState.h"

namespace device_emulator {

class StoppedState : public DeviceBehaviourState {
public:
    std::string ToString() const { return "Stopped"; }
};

} // namespace

#endif
