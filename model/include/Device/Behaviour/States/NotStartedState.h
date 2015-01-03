#ifndef _NOT_STARTED_STATE_H
#define _NOT_STARTED_STATE_H

#include "DeviceBehaviourState.h"
#include "Device/Behaviour/DeviceBehaviour.h"
#include "RunningState.h"

namespace device_emulator {

class NotStartedState : public DeviceBehaviourState {
public:
    static DeviceBehaviourStatePtr Instance();
    std::string ToString() const;
protected:
    void Start(const DeviceBehaviourPtr &context) const;
private:
    NotStartedState();
};

} // namespace

#endif
