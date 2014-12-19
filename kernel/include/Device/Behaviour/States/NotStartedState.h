#ifndef _NOT_STARTED_STATE_H
#define _NOT_STARTED_STATE_H

#include "DeviceBehaviourState.h"
#include "Device/Behaviour/DeviceBehaviour.h"
#include "RunningState.h"

namespace device_emulator {

class NotStartedState : public DeviceBehaviourState {
public:
    std::string ToString() const { return "NotStarted"; }
protected:
    void Start(const DeviceBehaviourPtr &context) const {
        transitionTo(context, DeviceBehaviourStatePtr(new RunningState()));
    }
};

} // namespace

#endif
