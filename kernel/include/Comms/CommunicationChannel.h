#ifndef _COMMUNICATION_CHANNEL_H
#define _COMMUNICATION_CHANNEL_H

#include <queue>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "Comms/CommunicationChannelSetup.h"
#include "Device/Behaviour/IDeviceBehaviour.h"
#include "Data/Message.h"

namespace device_emulator {

class CommunicationChannel;
typedef boost::shared_ptr<CommunicationChannel> ComChannelPtr;

class IDeviceBehaviour;
typedef boost::shared_ptr<IDeviceBehaviour> IDeviceBehaviourPtr;

/*!
    \class Interface for communication channels
*/
class CommunicationChannel {
public:

    CommunicationChannel(const ComChannelSetupPtr &setup) : _setup(setup) { };


    virtual ~CommunicationChannel() { }

    /*!
        \brief Starts the communication
        True if communication is stablished, False otherwise
    */
    virtual bool Start() = 0;

    /*!
        \brief Closes the communication
    */
    virtual void Close() = 0;

    /*!
        \brief Sends a message throught the channel
    */
    virtual void Send(const IMessagePtr &msg) = 0;

    /*!
        \brief Called when a message is received at the channel
    */
    virtual void MsgReceived(const IMessagePtr &msg);

    /*!
        \brief Used for Device behaviour for retrieving messages from the channel
    */
    bool WantMessage(const unsigned int msgID, const IDeviceBehaviourPtr &who);

private:

    /*!
        \brief True if the message has arrived, False otherwise
    */
    bool anyDeviceWaitingFor(const unsigned int msgID);

    /*!
        \brief True if the message has arrived, False otherwise
    */
    bool existsMessage(const unsigned int msgID);

    /*!
        \brief Adds a device behaviour to the waiting queue
    */
    void addWaitingForMessage(unsigned int msgId, const IDeviceBehaviourPtr &who);

    /*!
        \brief Queue of device behaviour for each kind of messages
               TODO: Encapsulate in custom class
               Hash { msgID } -> Queue { DeviceBehaviour }
    */
    std::map< unsigned int, std::queue< IDeviceBehaviourPtr > > _hashWaitingForMessage;

    /*!
        \brief Queue of messages for each kind of message
               TODO: Encapsulate in custom class
               Hash { msgID } -> Queue { Message }
    */
    std::map< unsigned int, std::queue< IMessagePtr > > _hashArrivedMessages;

    /*!
        \brief Protects critical section
    */
    boost::mutex _mutexMsgArrived;

    /*!
        \brief Setup of the channel
    */
    ComChannelSetupPtr _setup;
};

} // namespace
#endif
