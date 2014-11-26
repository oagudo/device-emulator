#ifndef _FINISHED_STATE_H
#define _FINISHED_STATE_h

#include "DeviceBehaviourState.h"

namespace device_emulator {

class FinishedState : public NonErrorState {
    bool AllowToContinue() { return false; }
};

} // namespace

#endif
