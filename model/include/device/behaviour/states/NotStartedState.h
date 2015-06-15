#ifndef _NOT_STARTED_STATE_H
#define _NOT_STARTED_STATE_H

#include "device/behaviour/states/DeviceBehaviourState.h"

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
