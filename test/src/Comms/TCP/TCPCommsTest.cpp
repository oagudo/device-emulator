#include <boost/test/auto_unit_test.hpp>

#include <Comms/TCP/TCPClient.h>
#include <Comms/TCP/TCPServer.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Data/Message.h>
#include <Device/Orders/OrderList.h>
#include <Device/Orders/IDeviceOrder.h>
#include <Device/Orders/ReceiveOrder.h>
#include <Device/Orders/SendOrder.h>


using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( TCPCommsTests )

struct Fixture {
    IMessagePtr msg1;
    TCPClientSetupPtr clientSetup;
    TCPClientPtr clientChannel;
    TCPServerSetupPtr serverSetup;
    TCPServerPtr serverChannel;
    IDeviceBehaviourPtr behaviourClient;
    IDeviceBehaviourPtr behaviourServer;
    OrderListPtr ordersClient;
    OrderListPtr ordersServer;
    IDeviceOrderPtr orderReceive;
    IDeviceOrderPtr orderSend;
    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        clientSetup(new TCPClientSetup("localhost", "2222")),
        clientChannel(new TCPClient(clientSetup)),
        serverSetup(new TCPServerSetup("2222")),
        serverChannel(new TCPServer(serverSetup)),
        behaviourClient(new DeviceBehaviour(clientChannel, "Test Behaviour")),
        behaviourServer(new DeviceBehaviour(serverChannel, "Test Behaviour2")),
        ordersClient(new OrderList),
        ordersServer(new OrderList),
        orderReceive(new ReceiveOrder(1, 250)),
        orderSend(new SendOrder(msg1))
    {
        ordersClient->Add(orderReceive);
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
    f.clientChannel->Send(f.msg1);
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) ); // Waits for message to be received
    BOOST_CHECK(f.serverChannel->WantMessage(f.msg1->GetId(), f.behaviourServer));
}

BOOST_AUTO_TEST_CASE( TCPCommsTests_DeviceBehavioursSendAndReceiveMessagesThroughtTCPChannel ) {
    Fixture f;
    f.serverChannel->Start();
    f.clientChannel->Start();

    f.behaviourServer->Start(f.ordersServer);
    f.behaviourClient->Start(f.ordersClient);

    f.behaviourServer->Wait();
    f.behaviourClient->Wait();
    
    BOOST_CHECK(f.behaviourServer->GetState()->IsErrorState() == false);
    BOOST_CHECK(f.behaviourClient->GetState()->IsErrorState() == false);
}

BOOST_AUTO_TEST_SUITE_END()
