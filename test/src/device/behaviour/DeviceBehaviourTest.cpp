#include <boost/test/auto_unit_test.hpp>
#include <boost/make_shared.hpp>
#include <data/Message.h>
#include <device/behaviour/DeviceBehaviour.h>
#include <device/behaviour/states/DeviceBehaviourState.h>
#include <device/behaviour/states/ErrorState.h>
#include <device/orders/OrderList.h>
#include <device/orders/InfiniteOrderList.h>
#include <device/orders/IDeviceOrder.h>
#include <device/orders/ReceiveOrder.h>
#include <device/orders/SendOrder.h>

#include "comms/mocks/CommunicationChannelMock.h"

using namespace device_emulator;

#define WAIT_TIME 50

BOOST_AUTO_TEST_SUITE( DeviceBehaviourTests )

struct Fixture {
    Message msg1;
    Message msg2;
    ComChannelPtr channel;
    OrderList orders;
    OrderList orders2;
    OrderList infSendOrders;
    DeviceBehaviourPtr behaviour;
    DeviceBehaviourPtr behaviour2;
    DeviceBehaviourPtr infiniteBehaviour;
    IDeviceOrderPtr orderReceive1;
    IDeviceOrderPtr orderReceive2;
    IDeviceOrderPtr orderSend1;
    IDeviceOrderPtr orderSend2;

    Fixture() :
        msg1(1, "msg1", "content1"),
        msg2(2, "msg2", "content2"),
        channel(boost::make_shared<CommsMock>()),
        orderReceive1(boost::make_shared<ReceiveOrder>(1, 250)),
        orderReceive2(boost::make_shared<ReceiveOrder>(2, 250)),
        orderSend1(boost::make_shared<SendOrder>(msg1)),
        orderSend2(boost::make_shared<SendOrder>(msg2))
    {
        orders.Add(orderReceive1);
        orders.Add(orderReceive2);
        orders2.Add(orderReceive1);
        orders2.Add(orderReceive2);
        infSendOrders.Add(orderSend1);
        infSendOrders.Add(orderSend2);

        behaviour = boost::make_shared<DeviceBehaviour>("Test Behaviour", channel, orders);
        behaviour2 = boost::make_shared<DeviceBehaviour>("Test Behaviour 2", channel, orders2);
        infiniteBehaviour = boost::make_shared<DeviceBehaviour>("Infinite behaviour", channel, infSendOrders);
    };
};

BOOST_AUTO_TEST_CASE( DeviceBehaviour_FinishedWithErrorWhenNoMessageIsReceived ) {
    Fixture f;
    f.behaviour->Start();
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState() == ErrorState::Instance());
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_WakesUpAfterReceivingAMessageWhichWasWaitingFor ) {
    Fixture f;
    f.behaviour->Start();
    boost::this_thread::sleep( boost::posix_time::milliseconds(WAIT_TIME) );
    f.channel->OnMsgReceived(f.msg1); // After WAIT_TIME ms the message is received, at this point thread should be wake up
    f.channel->OnMsgReceived(f.msg2);
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState() != ErrorState::Instance());
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_FinishedOKIfMessagesArePresent ) {
    Fixture f;
    f.channel->OnMsgReceived(f.msg1);
    f.channel->OnMsgReceived(f.msg2);
    f.behaviour->Start();
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState() != ErrorState::Instance());
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_CanBeStoppedAtAnyTime ) {
    Fixture f;
    f.infiniteBehaviour->Start(); // Infinite order list
    boost::this_thread::sleep( boost::posix_time::milliseconds(WAIT_TIME) );
    // After WAIT_TIME ms a stop is requested
    f.infiniteBehaviour->Stop();
    f.infiniteBehaviour->Wait();
    BOOST_CHECK(f.infiniteBehaviour->GetState() != ErrorState::Instance());
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_MessagesArePickedInOrder ) {
    Fixture f;
    f.channel->OnMsgReceived(f.msg1);
    f.channel->OnMsgReceived(f.msg2);
    f.behaviour->Start();
    boost::this_thread::sleep( boost::posix_time::milliseconds(WAIT_TIME) );
    f.behaviour2->Start(); // Second behaviour starts after first one
    f.behaviour2->Wait();
    BOOST_CHECK(f.behaviour->GetState() != ErrorState::Instance()); // First behaviour finished OK
    BOOST_CHECK(f.behaviour2->GetState() == ErrorState::Instance()); // Second behaviour did not receive nothing!
}

BOOST_AUTO_TEST_SUITE_END()
