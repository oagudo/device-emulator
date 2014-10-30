#ifndef _IDEVICE_BEHAVIOUR_STATE_H
#define _IDEVICE_BEHAVIOUR_STATE_H

namespace device_emulator {

class IDeviceBehaviourState;
typedef boost::shared_ptr<IDeviceBehaviourState> IDeviceBehaviourStatePtr;

/*!
    \class Represents a state of the device behaviour
*/
class IDeviceBehaviourState {

public:
    virtual ~IDeviceBehaviourState() { }
    virtual bool IsErrorState() = 0;
    virtual bool AllowToContinue() = 0;
    virtual std::string GetErrorMsg() { return "";}
};

/*!
    \class Represents a state which is not considered as error
*/
class NonErrorState : public IDeviceBehaviourState {
public:
    bool IsErrorState() { return false; }
    virtual bool AllowToContinue() { return true; }
};

} // namespace

#endif
