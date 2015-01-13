#ifndef _COMMUNICATION_CHANNEL_H
#define _COMMUNICATION_CHANNEL_H

#include <queue>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "Device/Behaviour/DeviceBehaviour.h"
#include "Data/Message.h"

namespace device_emulator {

class DeviceBehaviour;
typedef boost::shared_ptr<DeviceBehaviour> DeviceBehaviourPtr;

/*!
    \class Interface for communication channels
*/
    class CommunicationChannel : public boost::enable_shared_from_this<CommunicationChannel> {
public:

    CommunicationChannel();


    virtual ~CommunicationChannel();

    /*!
        \brief Starts the communication
        True if communication is stablished, False otherwise
    */
    virtual bool Start() = 0;

    /*!
        \brief Stops the communication
    */
    virtual void Stop() = 0;

    /*!
        \brief Sends a message throught the channel
    */
    virtual void Send(const IMessagePtr &msg) = 0;

    /*!
        \brief Called when a message is received at the channel
    */
    virtual void OnMsgReceived(const IMessagePtr &msg);

    /*!
        \brief Used for Device behaviour for retrieving messages from the channel
    */
    bool WantMessage(const unsigned int msgID, const DeviceBehaviourPtr &who);

protected:

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
    void addWaitingForMessage(unsigned int msgId, const DeviceBehaviourPtr &who);

    /*!
        \brief Queue of device behaviour for each kind of messages
               TODO: Encapsulate in custom class
               Hash { msgID } -> Queue { DeviceBehaviour }
    */
    std::map< unsigned int, std::queue< DeviceBehaviourPtr > > _hashWaitingForMessage;

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
};

} // namespace
#endif
