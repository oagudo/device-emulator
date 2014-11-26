#ifndef _STOPPED_STATE_H
#define _STOPPED_STATE_h

#include "DeviceBehaviourState.h"

namespace device_emulator {

class StoppedState : public NonErrorState {
    bool AllowToContinue() { return false; }
};

} // namespace

#endif
