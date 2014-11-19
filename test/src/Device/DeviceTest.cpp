#include <boost/test/auto_unit_test.hpp>

#include <Device/Device.h>
#include <Data/Message.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Device/Orders/OrderList.h>
#include <Device/Orders/IDeviceOrder.h>
#include <Device/Orders/ReceiveOrder.h>

#include "Comms/Mocks/CommunicationChannelMock.h"

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( DeviceTests )

struct Fixture {
    IMessagePtr msg1;
    IMessagePtr msg2;
    ComChannelPtr channel;
    OrderListPtr orders;
    OrderListPtr orders2;
    IDeviceBehaviourPtr behaviour;
    IDeviceBehaviourPtr behaviour2;
    IDeviceOrderPtr orderReceive1;
    IDeviceOrderPtr orderReceive2;
    DevicePtr device;

    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        msg2(new Message(2, "msg2", "content2")),
        channel(new CommsMock()),
        orders(new OrderList),
        orders2(new OrderList),
        behaviour(new DeviceBehaviour("Test Behaviour", channel, orders)),
        behaviour2(new DeviceBehaviour("Test Behaviour 2", channel, orders2)),
        orderReceive1(new ReceiveOrder(1, 250)),
        orderReceive2(new ReceiveOrder(2, 250)),
        device(new Device("Device test"))
    {
        orders->Add(orderReceive1);
        orders->Add(orderReceive2);
        orders2->Add(orderReceive1);
        orders2->Add(orderReceive2);
        device->AddBehaviour(behaviour);
        device->AddBehaviour(behaviour2);
    };
};

BOOST_AUTO_TEST_CASE( Device_StartsAllItsBehaviours ) {
    Fixture f;
    f.device->Start();
    f.behaviour->Wait();
    BOOST_CHECK(f.behaviour->GetState()->IsErrorState() == true);
}

BOOST_AUTO_TEST_SUITE_END()
