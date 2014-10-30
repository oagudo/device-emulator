#define BOOST_TEST_MODULE Device

#include <boost/test/auto_unit_test.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

#include <Data/Message.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Device/Orders/OrderList.h>
#include <Device/Orders/InfiniteOrderList.h>
#include <Device/Orders/IDeviceOrder.h>
#include <Device/Orders/ReceiveOrder.h>
#include <Device/Orders/SendOrder.h>

#include "Mocks/CommunicationChannelMock.h"

using namespace device_emulator;

// TODO: Organize tests in tests suites (different files)!! -> Change CMake configuration

struct Fixture {
    IMessagePtr msg1;
    IMessagePtr msg2;
    ComChannelPtr channel;
    IDeviceBehaviourPtr behaviour;
    OrderListPtr orders;
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
        orders(new OrderList),
        infSendOrders(new InfiniteOrderList),
        orderReceive1(new ReceiveOrder(1, 1000)),
        orderReceive2(new ReceiveOrder(2, 1000)),
        orderSend1(new SendOrder(msg1)),
        orderSend2(new SendOrder(msg2))
    {
        orders->Add(orderReceive1);
        orders->Add(orderReceive2);
        infSendOrders->Add(orderSend1);
        infSendOrders->Add(orderSend2);
    };
};

///////////////////////////////////////////////////////
// MESSAGE
///////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( Message_CanBeConvertedToVector ) {
    std::string contentTest("content of the message");
    Message msg(1, "Message Test", contentTest);
    std::vector<unsigned char> vector = msg.ToVector();

    // Same length
    BOOST_CHECK_EQUAL(vector.size(), contentTest.length());

    // Same content
    for(unsigned int i = 0; i < vector.size(); i++) {
            BOOST_CHECK_EQUAL(vector[i], (unsigned char)contentTest[i]);
    }
}

///////////////////////////////////////////////////////
// ORDER_LIST
///////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( OrderList_GrowsWhenNeeded ) {
    Fixture f;
    unsigned int numberOrders = f.orders->Count();
    f.orders->Add(IDeviceOrderPtr (new ReceiveOrder (1, 1000)));
    BOOST_CHECK_EQUAL(f.orders->Count(), numberOrders + 1);
}

BOOST_AUTO_TEST_CASE( OrderList_NextRemovesElementFromList ) {
    Fixture f;
    unsigned int numberOrders = f.orders->Count();
    f.orders->Next();
    BOOST_CHECK_EQUAL(f.orders->Count(), numberOrders - 1);    
}

BOOST_AUTO_TEST_CASE( OrderList_EmptyReturnsTrueIfThereAreNoOrders ) {
    Fixture f;
    while (f.orders->Count() > 0) {
      f.orders->Next();
    }
    BOOST_CHECK_EQUAL(f.orders->Empty(), true);    
}

///////////////////////////////////////////////////////
// INFINITE_ORDER_LIST
///////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( InfiniteOrderList_DoNotDecreaseWhenCallingNext ) {
    Fixture f;
    unsigned int numberOrders = f.infSendOrders->Count();
    f.infSendOrders->Next();
    BOOST_CHECK_EQUAL(f.infSendOrders->Count(), numberOrders);    
}

BOOST_AUTO_TEST_CASE( InfiniteOrderList_SetOrderAtTheEndWhenCallingNext )
{
    Fixture f;
    IDeviceOrderPtr order1 = f.infSendOrders->Next();
    BOOST_CHECK(order1 != f.infSendOrders->Next());    
}

///////////////////////////////////////////////////////
// COMMUNICATION_CHANNEL
///////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE( CommunicationChannel_ReceivedMessageIsReadyToBePicked ) {
    Fixture f;
    f.channel->MsgReceived(f.msg1);
    BOOST_CHECK(f.channel->WantMessage(f.msg1->GetId(), f.behaviour));
}

BOOST_AUTO_TEST_CASE( CommunicationChannel_NonReceivedMessageCannotBePicked ) {
    Fixture f;
    BOOST_CHECK(!f.channel->WantMessage(f.msg1->GetId(), f.behaviour));
}

BOOST_AUTO_TEST_CASE( CommunicationChannel_MessagesWaitingToBePickedAreDeliveried ) {
    Fixture f;
    f.channel->WantMessage(f.msg1->GetId(), f.behaviour);
    f.channel->MsgReceived(f.msg1);
    BOOST_CHECK(!f.channel->WantMessage(f.msg1->GetId(), f.behaviour)); // Already taken
}

///////////////////////////////////////////////////////
// DEVICE_BEHAVIOUR
///////////////////////////////////////////////////////

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
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == false);
}
