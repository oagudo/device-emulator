#include <boost/test/auto_unit_test.hpp>
#include <boost/make_shared.hpp>
#include <data/Message.h>
#include <device/behaviour/DeviceBehaviour.h>
#include <device/orders/OrderList.h>
#include "mocks/CommunicationChannelMock.h"

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( CommunicationChannelTests )

struct Fixture {
    Message msg1;
    Message msg2;
    ComChannelPtr channel;
    OrderList orders;

    Fixture() :
        msg1(1, "msg1", "content1"),
        msg2(2, "msg2", "content2"),
        channel(boost::make_shared<CommsMock>()) { };
};

BOOST_AUTO_TEST_CASE( CommunicationChannel_ReceivedMessageIsReadyToBePicked ) {
    Fixture f;
    f.channel->OnMsgReceived(f.msg1);
    BOOST_CHECK(f.channel->WantMessage(f.msg1.GetId(), [](const Message&) { }));
}

BOOST_AUTO_TEST_CASE( CommunicationChannel_NonReceivedMessageCannotBePicked ) {
    Fixture f;
    BOOST_CHECK(!f.channel->WantMessage(f.msg1.GetId(), [](const Message&) { }));
}

BOOST_AUTO_TEST_CASE( CommunicationChannel_MessagesWaitingToBePickedAreDeliveried ) {
    Fixture f;
    f.channel->WantMessage(f.msg1.GetId(), [](const Message&) { });
    f.channel->OnMsgReceived(f.msg1);
    BOOST_CHECK(!f.channel->WantMessage(f.msg1.GetId(), [](const Message&) { })); // Already taken
}

BOOST_AUTO_TEST_SUITE_END()
