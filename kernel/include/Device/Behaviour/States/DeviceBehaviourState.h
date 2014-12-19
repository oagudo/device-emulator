#ifndef _IDEVICE_BEHAVIOUR_STATE_H
#define _IDEVICE_BEHAVIOUR_STATE_H

namespace device_emulator {


class DeviceBehaviourState;
typedef boost::shared_ptr<DeviceBehaviourState> DeviceBehaviourStatePtr;

class DeviceBehaviour;
typedef boost::shared_ptr<DeviceBehaviour> DeviceBehaviourPtr;

/*!
    \class Represents a state of the device behaviour
*/
class DeviceBehaviourState {


public:
    virtual ~DeviceBehaviourState() { }
    virtual std::string ToString() const {return "Not implemented!";}
    
protected:
    void transitionTo(const DeviceBehaviourPtr &context, const DeviceBehaviourStatePtr &newState) const {
        context->transitionTo(newState);
    }

    void createExecutionThread(const DeviceBehaviourPtr &context) const {
        context->createExecutionThread();
    }

    friend class DeviceBehaviour;

    virtual void Enter(const DeviceBehaviourPtr &contex) const { }
    virtual void Start(const DeviceBehaviourPtr &context) const { }
    virtual void ExecuteOrders(const DeviceBehaviourPtr &context) const { }
    virtual void Stop(const DeviceBehaviourPtr &context) const { }
};


} // namespace

#endif
