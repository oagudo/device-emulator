#include <boost/test/auto_unit_test.hpp>

#include <Data/Message.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Device/Orders/OrderList.h>
#include <Device/Orders/InfiniteOrderList.h>
#include <Device/Orders/IDeviceOrder.h>
#include <Device/Orders/ReceiveOrder.h>
#include <Device/Orders/SendOrder.h>

#include "Mocks/CommunicationChannelMock.h"

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( DeviceBehaviourTests )

struct Fixture {
    IMessagePtr msg1;
    IMessagePtr msg2;
    ComChannelPtr channel;
    IDeviceBehaviourPtr behaviour;
    IDeviceBehaviourPtr behaviour2;
    OrderListPtr orders;
    OrderListPtr orders2;
    OrderListPtr infSendOrders;
    IDeviceOrderPtr orderReceive1;
    IDeviceOrderPtr orderReceive2;
    IDeviceOrderPtr orderSend1;
    IDeviceOrderPtr orderSend2;

    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        msg2(new Message(2, "msg2", "content2")),
        channel(new CommsMock()),
        behaviour(new DeviceBehaviour(channel, "Test Behaviour")),
        behaviour2(new DeviceBehaviour(channel, "Test Behaviour 2")),
        orders(new OrderList),
        orders2(new OrderList),
        infSendOrders(new InfiniteOrderList),
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
    f.behaviour->Start(f.orders);
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == true);
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_WakesUpAfterReceivingAMessageWhichWasWaitingFor ) {
    Fixture f;
    f.behaviour->Start(f.orders);
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) );
    f.channel->MsgReceived(f.msg1); // After 50 ms the message is received, at this point thread should be wake up
    f.channel->MsgReceived(f.msg2);
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == false);
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_FinishedOKIfMessagesArePresent ) {
    Fixture f;
    f.channel->MsgReceived(f.msg1);
    f.channel->MsgReceived(f.msg2);
    f.behaviour->Start(f.orders);
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == false);
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_CanBeStoppedAtAnyTime ) {
    Fixture f;
    f.behaviour->Start(f.infSendOrders); // Infinite order list
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) );
    // After 50 ms a stop is requested
    f.behaviour->Stop();
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == false);
}

BOOST_AUTO_TEST_CASE( DeviceBehaviour_MessagesArePickedInOrder ) {
    Fixture f;
    f.channel->MsgReceived(f.msg1);
    f.channel->MsgReceived(f.msg2);
    f.behaviour->Start(f.orders);
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) );
    f.behaviour2->Start(f.orders2); // Second behaviour starts after first one
    f.behaviour2->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == false); // First behaviour finished OK
    BOOST_CHECK(f.behaviour2->GetState()->IsErrorState() == true); // Second behaviour did not receive nothing!
}

BOOST_AUTO_TEST_SUITE_END()
