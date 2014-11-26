#include <boost/test/auto_unit_test.hpp>

#include <Comms/TCP/TCPClient.h>
#include <Comms/TCP/TCPServer.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Device/Behaviour/States/DeviceBehaviourState.h>
#include <Data/Message.h>
#include <Device/Orders/OrderList.h>
#include <Device/Orders/IDeviceOrder.h>
#include <Device/Orders/ReceiveOrder.h>
#include <Device/Orders/SendOrder.h>
#include <Device/Orders/WaitOrder.h>


using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( TCPCommsTests )

struct Fixture {
    IMessagePtr msg1;
    TCPClientSetupPtr clientSetup;
    TCPClientPtr clientChannel;
    TCPServerSetupPtr serverSetup;
    TCPServerPtr serverChannel;
    OrderListPtr ordersClient;
    OrderListPtr ordersServer;
    IDeviceBehaviourPtr behaviourClient;
    IDeviceBehaviourPtr behaviourServer;
    IDeviceOrderPtr orderReceive;
    IDeviceOrderPtr orderSend;
    IDeviceOrderPtr orderWait;
    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        clientSetup(new TCPClientSetup("localhost", "2222")),
        clientChannel(new TCPClient(clientSetup)),
        serverSetup(new TCPServerSetup("2222")),
        serverChannel(new TCPServer(serverSetup)),
        ordersClient(new OrderList),
        ordersServer(new OrderList),
        behaviourClient(new DeviceBehaviour("Test Behaviour", clientChannel, ordersClient)),
        behaviourServer(new DeviceBehaviour("Test Behaviour2", serverChannel, ordersServer)),
        orderReceive(new ReceiveOrder(1, 250)),
        orderSend(new SendOrder(msg1)),
        orderWait(new WaitOrder(50))
    {
        ordersClient->Add(orderReceive);
        ordersServer->Add(orderWait);
        ordersServer->Add(orderSend);
    };

    ~Fixture()
    {
        clientChannel->Stop();
        serverChannel->Stop();
    }
    
};

BOOST_AUTO_TEST_CASE( TCPCommsTests_ServerStartsListenningCorrectly ) {
    Fixture f;
    BOOST_CHECK (f.serverChannel->Start());
}

BOOST_AUTO_TEST_CASE( TCPCommsTests_ClientConnectsToServerCorrectly ) {
    Fixture f;
    f.serverChannel->Start();
    BOOST_CHECK(f.clientChannel->Start());
}

BOOST_AUTO_TEST_CASE( TCPCommsTests_MessagesAreSentAndReceivedCorrectly ) {
    Fixture f;
    f.serverChannel->Start();
    f.clientChannel->Start();
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) ); // Waits for connection
    f.clientChannel->Send(f.msg1);
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) ); // Waits for message to be received
    BOOST_CHECK(f.serverChannel->WantMessage(f.msg1->GetId(), f.behaviourServer));
}

BOOST_AUTO_TEST_CASE( TCPCommsTests_DeviceBehavioursSendAndReceiveMessagesThroughtTCPChannel ) {
    Fixture f;
    f.serverChannel->Start();
    f.clientChannel->Start();

    f.behaviourServer->Start();
    f.behaviourClient->Start();

    f.behaviourServer->Wait();
    f.behaviourClient->Wait();
    
    BOOST_CHECK(f.behaviourServer->GetState()->IsErrorState() == false);
    BOOST_CHECK(f.behaviourClient->GetState()->IsErrorState() == false);
}

BOOST_AUTO_TEST_SUITE_END()
