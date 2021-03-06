#ifndef _RUNNING_STATE_H
#define _RUNNING_STATE_H

#include "device/behaviour/states/DeviceBehaviourState.h"

namespace device_emulator {

class RunningState : public DeviceBehaviourState {
public:

    static DeviceBehaviourStatePtr Instance();
    std::string ToString() const;

protected:
    void Enter(const DeviceBehaviourPtr &context) const;
    void ExecuteOrders(const DeviceBehaviourPtr &context) const;
    void Stop(const DeviceBehaviourPtr &context) const;
    void Wait(const DeviceBehaviourPtr &context) const;

private:

    RunningState();
};

} // namespace

#endif
