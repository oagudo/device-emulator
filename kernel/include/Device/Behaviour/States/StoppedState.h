#ifndef _STOPPED_STATE_H
#define _STOPPED_STATE_H

#include "DeviceBehaviourState.h"

namespace device_emulator {

class StoppedState : public NonErrorState {
public:
    bool AllowToContinue() { return false; }
};

} // namespace

#endif
