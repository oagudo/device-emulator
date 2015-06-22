#ifndef _RECEIVE_ORDER_H
#define _RECEIVE_ORDER_H

#include "device/orders/IDeviceOrder.h"
#include "data/Message.h"
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/optional.hpp>

namespace device_emulator {

/*!
    \class Represents an order for receiving a message
*/
class ReceiveOrder : public IDeviceOrder
{
public:
    ReceiveOrder(const unsigned int msgID, const unsigned int timeout);
    ReceiveOrder(const ReceiveOrder& other);
    const ReceiveOrder& operator=(const ReceiveOrder& other);

    bool Execute(const DeviceBehaviourPtr &context);

    IDeviceOrderPtr Clone() const;
private:

    void onMessageArrived(const DeviceBehaviourPtr &context,
                          const Message &msg);

    bool waitForMessageReception(const DeviceBehaviourPtr &context,
                                 const unsigned int milliseconds);
    /*!
        \brief Message received
    */
    boost::optional<Message> _msgReceived;

    /*
        \brief Protects critical sections for receiving message
    */
    boost::condition_variable _receiveMsgCondition;
    boost::mutex _mutexCondition;


    /*!
        \brief Expected ID of message received
     */
    unsigned int _msgID;
    /*!
        \brief Maximum time for receiving the message
     */
    unsigned int _timeout;
};

} // namespace

#endif
