#include <boost/test/auto_unit_test.hpp>
#include <boost/make_shared.hpp>
#include <device/Device.h>
#include <data/Message.h>
#include <device/behaviour/DeviceBehaviour.h>
#include <device/behaviour/states/DeviceBehaviourState.h>
#include <device/behaviour/states/StoppedState.h>
#include <device/behaviour/states/ErrorState.h>
#include <device/orders/OrderList.h>
#include <device/orders/InfiniteOrderList.h>
#include <device/orders/IDeviceOrder.h>
#include <device/orders/ReceiveOrder.h>
#include <device/orders/SendOrder.h>

#include "comms/mocks/CommunicationChannelMock.h"

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( DeviceTests )

struct Fixture {
    Message msg1;
    Message msg2;
    ComChannelPtr channel;
    OrderList orders;
    OrderList orders2;
    InfiniteOrderList infSendOrders;
    DeviceBehaviourPtr behaviour;
    DeviceBehaviourPtr behaviour2;
    DeviceBehaviourPtr infiniteBehaviour;
    IDeviceOrderPtr orderReceive1;
    IDeviceOrderPtr orderReceive2;
    IDeviceOrderPtr orderSend1;
    Device device;

    Fixture() :
        msg1(1, "msg1", "content1"),
        msg2(2, "msg2", "content2"),
        channel(boost::make_shared<CommsMock>()),
        orderReceive1(boost::make_shared<ReceiveOrder>(1, 2500)),
        orderReceive2(boost::make_shared<ReceiveOrder>(2, 2500)),
        orderSend1(boost::make_shared<SendOrder>(msg1)),
        device("Device test")
    {
        orders.Add(orderReceive1);
        orders.Add(orderReceive2);
        orders2.Add(orderReceive1);
        orders2.Add(orderReceive2);
        infSendOrders.Add(orderSend1);

        behaviour = boost::make_shared<DeviceBehaviour>("Test Behaviour", channel, orders);
        behaviour2 = boost::make_shared<DeviceBehaviour>("Test Behaviour 2", channel, orders2);
        infiniteBehaviour = boost::make_shared<DeviceBehaviour>("Infinite behaviour", channel, infSendOrders);

        device.AddBehaviour(behaviour);
        device.AddBehaviour(behaviour2);
    };
};

BOOST_AUTO_TEST_CASE( Device_StartsAllItsBehaviours ) {
    Fixture f;
    // Behaviours have not been started yet
    f.device.Start();
    f.behaviour->Wait();
    f.behaviour2->Wait();
    // Behaviours have finished (with errors)
    BOOST_CHECK(f.behaviour->GetState() == ErrorState::Instance());
    BOOST_CHECK(f.behaviour2->GetState() == ErrorState::Instance());
}

BOOST_AUTO_TEST_CASE( Device_StopsAllItsBehaviours ) {
    Fixture f;
    f.device.AddBehaviour(f.infiniteBehaviour);
    f.device.Start();
    f.device.Stop();
    f.behaviour->Wait();
    f.behaviour2->Wait();
    f.infiniteBehaviour->Wait();
    BOOST_CHECK(f.infiniteBehaviour->GetState() == StoppedState::Instance());
}

BOOST_AUTO_TEST_SUITE_END()
