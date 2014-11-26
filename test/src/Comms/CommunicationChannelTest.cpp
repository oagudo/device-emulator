#include <boost/test/auto_unit_test.hpp>

#include <Data/Message.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Device/Orders/OrderList.h>
#include "Mocks/CommunicationChannelMock.h"

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( CommunicationChannelTests )

struct Fixture {
    IMessagePtr msg1;
    IMessagePtr msg2;
    ComChannelPtr channel;
    OrderListPtr orders;
    DeviceBehaviourPtr behaviour;

    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        msg2(new Message(2, "msg2", "content2")),
        channel(new CommsMock()),
        orders(new OrderList),
        behaviour(new DeviceBehaviour("Test Behaviour", channel, orders)) {
    };
};

BOOST_AUTO_TEST_CASE( CommunicationChannel_ReceivedMessageIsReadyToBePicked ) {
    Fixture f;
    f.channel->OnMsgReceived(f.msg1);
    BOOST_CHECK(f.channel->WantMessage(f.msg1->GetId(), f.behaviour));
}

BOOST_AUTO_TEST_CASE( CommunicationChannel_NonReceivedMessageCannotBePicked ) {
    Fixture f;
    BOOST_CHECK(!f.channel->WantMessage(f.msg1->GetId(), f.behaviour));
}

BOOST_AUTO_TEST_CASE( CommunicationChannel_MessagesWaitingToBePickedAreDeliveried ) {
    Fixture f;
    f.channel->WantMessage(f.msg1->GetId(), f.behaviour);
    f.channel->OnMsgReceived(f.msg1);
    BOOST_CHECK(!f.channel->WantMessage(f.msg1->GetId(), f.behaviour)); // Already taken
}

BOOST_AUTO_TEST_SUITE_END()
