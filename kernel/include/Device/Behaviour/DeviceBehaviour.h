#ifndef _DEVICE_BEHAVIOUR_H
#define _DEVICE_BEHAVIOUR_H

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Device/Behaviour/IDeviceBehaviour.h"

namespace device_emulator {

class DeviceBehaviour : public IDeviceBehaviour, public boost::enable_shared_from_this<DeviceBehaviour> {
public:
    
    DeviceBehaviour(const ComChannelPtr &channel, const std::string &behaviourName);

    virtual ~DeviceBehaviour() { }

    IDeviceBehaviourStatePtr GetState();

    void Start(OrderListPtr &orders);

    void Stop();

    void Wait();

    void OnMessageArrived(const IMessagePtr &msg);

    void WaitForMessageReception(const unsigned int milliseconds);

    ComChannelPtr GetCommChannel();

private:

    /*!
        \brief Method executed in a separate thread
    */
    void behave(OrderListPtr &orders);

    ComChannelPtr _channel;
    std::string _behaviourName;
    IDeviceBehaviourStatePtr _state;

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

};

} // namespace

#endif
