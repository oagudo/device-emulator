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
    virtual bool IsErrorState() = 0;
    virtual bool AllowToContinue() = 0;
    virtual std::string GetErrorMsg() { return ""; }
    virtual void Start(const DeviceBehaviourPtr &context) { }
    virtual void ExecuteOrders(const DeviceBehaviourPtr &context) { }
    virtual void Stop(const DeviceBehaviourPtr &context) { }
protected:
    void transitionTo(const DeviceBehaviourPtr &context, const DeviceBehaviourStatePtr &newState) {
        context->transitionTo(newState);
    }
};
/*!
    \class Represents a state which is not considered as error
*/
class NonErrorState : public DeviceBehaviourState {
public:
    bool IsErrorState() { return false; }
    virtual bool AllowToContinue() { return true; }
};

} // namespace

#endif
