#ifndef _FINISHED_STATE_H
#define _FINISHED_STATE_H

#include "DeviceBehaviourState.h"

namespace device_emulator {

class FinishedState : public NonErrorState {
public:
    bool AllowToContinue() { return false; }
};

} // namespace

#endif
