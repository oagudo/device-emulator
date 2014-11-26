#include <boost/test/auto_unit_test.hpp>

#include <Data/Message.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Device/Behaviour/States/DeviceBehaviourState.h>
#include <Device/Orders/OrderList.h>
#include <Device/Orders/InfiniteOrderList.h>
#include <Device/Orders/IDeviceOrder.h>
#include <Device/Orders/ReceiveOrder.h>
#include <Device/Orders/SendOrder.h>

#include "Comms/Mocks/CommunicationChannelMock.h"

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( DeviceBehaviourTests )

struct Fixture {
    IMessagePtr msg1;
    IMessagePtr msg2;
    ComChannelPtr channel;
    OrderListPtr orders;
    OrderListPtr orders2;
    OrderListPtr infSendOrders;
    IDeviceBehaviourPtr behaviour;
    IDeviceBehaviourPtr behaviour2;
    IDeviceBehaviourPtr infiniteBehaviour;
    IDeviceOrderPtr orderReceive1;
    IDeviceOrderPtr orderReceive2;
    IDeviceOrderPtr orderSend1;
    IDeviceOrderPtr orderSend2;

    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        msg2(new Message(2, "msg2", "content2")),
        channel(new CommsMock()),
        orders(new OrderList),
        orders2(new OrderList),
        infSendOrders(new InfiniteOrderList),
        behaviour(new DeviceBehaviour("Test Behaviour", channel, orders)),
        behaviour2(new DeviceBehaviour("Test Behaviour 2", channel, orders2)),
        infiniteBehaviour(new DeviceBehaviour("Infinite behaviour", channel, infSendOrders)),
        orderReceive1(new ReceiveOrder(1, 250)),
        orderReceive2(new ReceiveOrder(2, 250)),
        orderSend1(new SendOrder(msg1)),
        orderSend2(new SendOrder(msg2))
    {
        orders->Add(orderReceive1);
        orders->Add(orderReceive2);
        orders2->Add(orderReceive1);
        orders2->Add(orderReceive2);
        infSendOrders->Add(orderSend1);
        infSendOrders->Add(orderSend2);
    };
};

BOOST_AUTO_TEST_CASE( DeviceBehaviour_FinishedWithErrorWhenNoMessageIsReceived ) {
    Fixture f;
    f.behaviour->Start();
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == true);
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_WakesUpAfterReceivingAMessageWhichWasWaitingFor ) {
    Fixture f;
    f.behaviour->Start();
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) );
    f.channel->OnMsgReceived(f.msg1); // After 50 ms the message is received, at this point thread should be wake up
    f.channel->OnMsgReceived(f.msg2);
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == false);
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_FinishedOKIfMessagesArePresent ) {
    Fixture f;
    f.channel->OnMsgReceived(f.msg1);
    f.channel->OnMsgReceived(f.msg2);
    f.behaviour->Start();
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == false);
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_CanBeStoppedAtAnyTime ) {
    Fixture f;
    f.infiniteBehaviour->Start(); // Infinite order list
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) );
    // After 50 ms a stop is requested
    f.infiniteBehaviour->Stop();
    f.infiniteBehaviour->Wait();
    BOOST_CHECK(f.infiniteBehaviour->GetState()->IsErrorState() == false);
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_MessagesArePickedInOrder ) {
    Fixture f;
    f.channel->OnMsgReceived(f.msg1);
    f.channel->OnMsgReceived(f.msg2);
    f.behaviour->Start();
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) );
    f.behaviour2->Start(); // Second behaviour starts after first one
    f.behaviour2->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == false); // First behaviour finished OK
    BOOST_CHECK(f.behaviour2->GetState()->IsErrorState() == true); // Second behaviour did not receive nothing!
}

BOOST_AUTO_TEST_SUITE_END()
