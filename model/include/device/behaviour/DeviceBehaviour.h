#ifndef _DEVICE_BEHAVIOUR_H
#define _DEVICE_BEHAVIOUR_H

#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "data/Message.h"
#include "Common.h"

namespace device_emulator {

class DeviceBehaviour : public boost::enable_shared_from_this<DeviceBehaviour> {
public:
    
    DeviceBehaviour(const std::string &name, const ComChannelPtr &channel, const IOrderList &orders);

    virtual ~DeviceBehaviour();

    DeviceBehaviourStatePtr GetState() const;

    std::string GetName() const;

    IOrderList& GetOrders();

    ComChannelPtr GetCommChannel();

    void Start();

    void Stop();

    void Wait();

private:

    friend class ReceiveOrder;

    void onMessageArrived(const Message &msg);
    void waitForMessageReception(const unsigned int milliseconds);

    friend class DeviceBehaviourState;

    void transitionTo(const DeviceBehaviourStatePtr &newState);

    /*!
        \brief Method executed in a separate thread
    */
    void executeOrders();

    /*!
        \brief Creates the execution thread
     */
    void createExecutionThread();

    /*!
        \brief Waits the execution thread
     */
    void waitExecutionThread();

    /*!
        \brief Protects critical sectionds
    */
    boost::mutex _mutexCondition;
    boost::condition_variable _condition;

    /*!
        \brief Executing thread
    */
    boost::thread _behaviourThread;

    /*!
        \brief Last message received
    */
    Message _msgReceived;


    std::string _name;

    /*!
        \brief Communication channel used for exchanging messages
     */
    ComChannelPtr _channel;

    /*!
        \brief List of orders executed by the behaviour
     */
    IOrderListScopedPtr _orders;

    /*!
        \brief Holds the state of the behaviour
    */
    DeviceBehaviourStatePtr _state;
};

} // namespace

#endif
