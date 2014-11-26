#ifndef _NOT_STARTED_STATE_H
#define _NOT_STARTED_STATE_h

#include "DeviceBehaviourState.h"
#include "Device/Behaviour/IDeviceBehaviour.h"
#include "RunningState.h"

namespace device_emulator {

class NotStartedState : public NonErrorState {
public:
    void Start(const IDeviceBehaviourPtr &context) {
        context->TransitionTo(DeviceBehaviourStatePtr(new RunningState()));
    }
};

} // namespace

#endif
