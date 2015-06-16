#ifndef _COMMUNICATION_CHANNEL_H
#define _COMMUNICATION_CHANNEL_H

#include <queue>
#include <map>
#include <boost/thread/mutex.hpp>
#include "Common.h"

namespace device_emulator {

/*!
    \class Interface for communication channels
*/
class CommunicationChannel {
public:

    CommunicationChannel();

    virtual ~CommunicationChannel();

    /*!
        \brief Starts the communication
        True if communication is established, False otherwise
    */
    virtual bool Start() = 0;

    /*!
        \brief Stops the communication
    */
    virtual void Stop() = 0;

    /*!
        \brief Sends a message throught the channel
    */
    virtual void Send(const Message &msg) = 0;

    /*!
        \brief Called when a message is received at the channel
    */
    virtual void OnMsgReceived(const Message &msg);

    /*!
        \brief Used for retrieving messages from the channel
    */
    bool WantMessage(const unsigned int msgID, const ComChannelReceiveCallback &callback);

protected:

    /*!
        \brief True if the message has arrived, False otherwise
    */
    bool anyWaitingForMessage(const unsigned int msgID);

    /*!
        \brief True if the message has arrived, False otherwise
    */
    bool existsMessage(const unsigned int msgID);

    /*!
        \brief Adds a device behaviour to the waiting queue
    */
    void addWaitingForMessage(unsigned int msgId, const ComChannelReceiveCallback &callback);

    /*!
        \brief Queue of callbacks for each kind of messages
               TODO: Encapsulate in custom class
               Hash { msgID } -> Queue { ComChannelReceiveCallback }
    */
    std::map< unsigned int, std::queue< ComChannelReceiveCallback > > _hashWaitingForMessage;

    /*!
        \brief Queue of messages for each kind of message
               TODO: Encapsulate in custom class
               Hash { msgID } -> Queue { Message }
    */
    std::map< unsigned int, std::queue< Message > > _hashArrivedMessages;

    /*!
        \brief Protects critical section
    */
    boost::mutex _mutexMsgArrived;
};

} // namespace
#endif
