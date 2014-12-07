#ifndef _DEVICE_BEHAVIOUR_H
#define _DEVICE_BEHAVIOUR_H

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace device_emulator {

class DeviceBehaviour;
typedef boost::shared_ptr<DeviceBehaviour> DeviceBehaviourPtr;

class CommunicationChannel;
typedef boost::shared_ptr<CommunicationChannel> ComChannelPtr;

class OrderList;
typedef boost::shared_ptr<OrderList> OrderListPtr;

class DeviceBehaviourState;
typedef boost::shared_ptr<DeviceBehaviourState> DeviceBehaviourStatePtr;

class IMessage;
typedef boost::shared_ptr<IMessage> IMessagePtr;

class DeviceBehaviour : public boost::enable_shared_from_this<DeviceBehaviour> {
public:
    
    DeviceBehaviour(const std::string &name, const ComChannelPtr &channel, const OrderListPtr &orders);

    virtual ~DeviceBehaviour() { }

    DeviceBehaviourStatePtr GetState() const;

    std::string GetName() const;

    OrderListPtr GetOrders();

    ComChannelPtr GetCommChannel();

    void Start();

    void Stop();

    void Wait();

private:

    friend class CommunicationChannel;

    void onMessageArrived(const IMessagePtr &msg);

    friend class ReceiveOrder;

    void waitForMessageReception(const unsigned int milliseconds);

    friend class DeviceBehaviourState;

    void transitionTo(const DeviceBehaviourStatePtr &newState);

    /*!
        \brief Method executed in a separate thread
    */
    void executeOrders();

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
    IMessagePtr _msgReceived;


    std::string _name;

    /*!
      \brief Communication channel used for exchanging messages
     */
    ComChannelPtr _channel;

    /*!
      \brief List of orders executed by the behaviour
     */
    OrderListPtr _orders;


    DeviceBehaviourStatePtr _state;
};

} // namespace

#endif
