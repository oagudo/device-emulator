#include <boost/test/auto_unit_test.hpp>

#include <Device/Device.h>
#include <Data/Message.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Device/Behaviour/States/DeviceBehaviourState.h>
#include <Device/Behaviour/States/StoppedState.h>
#include <Device/Behaviour/States/ErrorState.h>
#include <Device/Orders/OrderList.h>
#include <Device/Orders/InfiniteOrderList.h>
#include <Device/Orders/IDeviceOrder.h>
#include <Device/Orders/ReceiveOrder.h>
#include <Device/Orders/SendOrder.h>

#include "Comms/Mocks/CommunicationChannelMock.h"

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( DeviceTests )

struct Fixture {
    IMessagePtr msg1;
    IMessagePtr msg2;
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
    DevicePtr device;

    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        msg2(new Message(2, "msg2", "content2")),
        channel(new CommsMock()),
        orderReceive1(new ReceiveOrder(1, 2500)),
        orderReceive2(new ReceiveOrder(2, 2500)),
        orderSend1(new SendOrder(msg1)),
        device(new Device("Device test"))
    {
        orders.Add(orderReceive1);
        orders.Add(orderReceive2);
        orders2.Add(orderReceive1);
        orders2.Add(orderReceive2);
        infSendOrders.Add(orderSend1);

        behaviour.reset(new DeviceBehaviour("Test Behaviour", channel, orders));
        behaviour2.reset(new DeviceBehaviour("Test Behaviour 2", channel, orders2));
        infiniteBehaviour.reset(new DeviceBehaviour("Infinite behaviour", channel, infSendOrders));

        device->AddBehaviour(behaviour);
        device->AddBehaviour(behaviour2);
    };
};

BOOST_AUTO_TEST_CASE( Device_StartsAllItsBehaviours ) {
    Fixture f;
    // Behaviours have not been started yet
    f.device->Start();
    f.behaviour->Wait();
    f.behaviour2->Wait();
    // Behaviours have finished (with errors)
    BOOST_CHECK(f.behaviour->GetState() == ErrorState::Instance());
    BOOST_CHECK(f.behaviour2->GetState() == ErrorState::Instance());
}

BOOST_AUTO_TEST_CASE( Device_StopsAllItsBehaviours ) {
    Fixture f;
    f.device->AddBehaviour(f.infiniteBehaviour);
    f.device->Start();
    f.device->Stop();
    f.behaviour->Wait();
    f.behaviour2->Wait();
    f.infiniteBehaviour->Wait();
    BOOST_CHECK(f.infiniteBehaviour->GetState() == StoppedState::Instance());
}

BOOST_AUTO_TEST_SUITE_END()
