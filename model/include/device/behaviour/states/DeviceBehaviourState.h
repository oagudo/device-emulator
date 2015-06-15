#ifndef _IDEVICE_BEHAVIOUR_STATE_H
#define _IDEVICE_BEHAVIOUR_STATE_H

#include "device/behaviour/DeviceBehaviour.h"

namespace device_emulator {

/*!
    \class Represents a state of the device behaviour
*/
class DeviceBehaviourState {

public:
    virtual ~DeviceBehaviourState() { }
    virtual std::string ToString() const = 0;

protected:
    void transitionTo(const DeviceBehaviourPtr &context, const DeviceBehaviourStatePtr &newState) const {
        context->transitionTo(newState);
    }

    void createExecutionThread(const DeviceBehaviourPtr &context) const {
        context->createExecutionThread();
    }

    void waitExecutionThread(const DeviceBehaviourPtr &context) const {
        context->waitExecutionThread();
    }

    friend class DeviceBehaviour;

    virtual void Enter(const DeviceBehaviourPtr &contex) const { }
    virtual void Start(const DeviceBehaviourPtr &context) const { }
    virtual void ExecuteOrders(const DeviceBehaviourPtr &context) const { }
    virtual void Stop(const DeviceBehaviourPtr &context) const { }
    virtual void Wait(const DeviceBehaviourPtr &context) const { }
};


} // namespace

#endif
