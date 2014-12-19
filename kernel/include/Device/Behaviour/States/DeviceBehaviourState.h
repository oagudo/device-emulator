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
    virtual bool AllowToContinue() = 0;
    virtual std::string ToString() {return "Not implemented!";}
    
protected:
    void transitionTo(const DeviceBehaviourPtr &context, const DeviceBehaviourStatePtr &newState) {
        context->transitionTo(newState);
    }

    void createExecutionThread(const DeviceBehaviourPtr &context) {
        context->createExecutionThread();
    }

    friend class DeviceBehaviour;

    virtual void Enter(const DeviceBehaviourPtr &contex) { }
    virtual void Start(const DeviceBehaviourPtr &context) { }
    virtual void ExecuteOrders(const DeviceBehaviourPtr &context) { }
    virtual void Stop(const DeviceBehaviourPtr &context) { }
};
/*!
    \class Represents a state which is not considered as error
*/
class NonErrorState : public DeviceBehaviourState {
public:
    virtual bool AllowToContinue() { return true; }
};

} // namespace

#endif
