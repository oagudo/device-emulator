#ifndef _IDEVICE_BEHAVIOUR_H
#define _IDEVICE_BEHAVIOUR_H

#include <boost/shared_ptr.hpp>
#include "Device/Behaviour/States/IDeviceBehaviourState.h"
#include "Data/IMessage.h"

namespace device_emulator {

class IDeviceBehaviour;
typedef boost::shared_ptr<IDeviceBehaviour> IDeviceBehaviourPtr;

class CommunicationChannel;
typedef boost::shared_ptr<CommunicationChannel> ComChannelPtr;

class OrderList;
typedef boost::shared_ptr<OrderList> OrderListPtr;

/*!
    \class Interface for a device behaviour. A device behaviour could be: Polling, initial Handshaking, etc.
*/
class IDeviceBehaviour {
public:
    IDeviceBehaviour(const std::string &name) : _name(name) { }

    virtual ~IDeviceBehaviour() { };
    /*!
        \brief Starts behaving
    */
    virtual void Start(OrderListPtr &orders) = 0;

    /*!
        \brief Stops current behaviour
    */
    virtual void Stop() = 0;

    /*!
        \brief Wait until behaviour finished
    */
    virtual void Wait() = 0;

    /*!
        \brief Callback used for receiving a message
    */
    virtual void OnMessageArrived(const IMessagePtr &msg) = 0;

    /*!
        \brief Gets the state of the behaviour
    */
    virtual IDeviceBehaviourStatePtr GetState() = 0;

    /*!
        \brief Waits n milliseconds until receive a message
    */
    virtual void WaitForMessageReception(const unsigned int milliseconds) = 0;

    /*!
        \brief Returns the current communication channel
    */
    virtual ComChannelPtr GetCommChannel() = 0;

    std::string GetName() const { return _name; }

protected:

    std::string _name;

};

} // namespace

#endif
