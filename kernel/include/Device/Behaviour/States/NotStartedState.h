#ifndef _NOT_STARTED_STATE_H
#define _NOT_STARTED_STATE_H

#include "DeviceBehaviourState.h"
#include "Device/Behaviour/DeviceBehaviour.h"
#include "RunningState.h"

namespace device_emulator {

class NotStartedState : public NonErrorState {
public:
    bool AllowToContinue() { return false; }
protected:
    void Start(const DeviceBehaviourPtr &context) {
        transitionTo(context, DeviceBehaviourStatePtr(new RunningState()));
    }
};

} // namespace

#endif
